#!/bin/bash

# Get the directory where the script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CONFIG_FILE="$SCRIPT_DIR/server_config.json"

# Check if jq is installed
if ! command -v jq &> /dev/null; then
    echo "Error: jq is required but not installed. Please install it first:"
    echo "sudo apt-get install jq"
    exit 1
fi

# Load configuration
if [ ! -f "$CONFIG_FILE" ]; then
    echo "Error: Configuration file not found at $CONFIG_FILE"
    exit 1
fi

# Read configuration
PORT=$(jq -r '.port' "$CONFIG_FILE")
TIMEOUT=$(jq -r '.timeout' "$CONFIG_FILE")

# Test data for the Black-Scholes endpoint
JSON_DATA='{
    "spot_price": 100.0,
    "strike_price": 100.0,
    "risk_free_rate": 0.05,
    "time_to_maturity": 1.0,
    "volatility": 0.2,
    "is_call": true
}'

# Function to check if an IP is reachable
check_ping() {
    local ip=$1
    local name=$2
    if [[ "$ip" == "127.0.0.1" || "$ip" == "localhost" ]]; then
        return 0  # Skip ping for localhost
    fi
    ping -c 1 -W 1 "$ip" >/dev/null 2>&1
    return $?
}

# Function to test a single server
test_server() {
    local name=$1
    local ip=$2
    echo "Testing server '$name' at $ip:$PORT..."
    
    # Check if IP is reachable first (skip for localhost)
    if ! check_ping "$ip" "$name"; then
        echo "✗ Server '$name' is not reachable"
        return 1
    fi
    
    # Use curl with timeout
    response=$(curl -s -X POST "http://$ip:$PORT/api/v1/pricing/black-scholes" \
        -H "Content-Type: application/json" \
        -d "$JSON_DATA" \
        --connect-timeout "$TIMEOUT")
    
    if [ $? -eq 0 ] && [ ! -z "$response" ]; then
        echo "✓ Server '$name' is responding"
        echo "Response: $response"
        # Save the working server name to a temporary file
        echo "$name" > /tmp/last_working_server_name
        return 0
    else
        echo "✗ No response from server '$name'"
        return 1
    fi
}

# Main script
echo "Starting server discovery..."
echo "Timestamp: $(date)"
found_server=false

# If we have a last working server, try it first
if [ -f /tmp/last_working_server_name ]; then
    last_name=$(cat /tmp/last_working_server_name)
    last_ip=$(jq -r ".servers.\"$last_name\"" "$CONFIG_FILE")
    echo "Trying last known working server '$last_name'..."
    if test_server "$last_name" "$last_ip"; then
        found_server=true
        echo "Successfully connected to last known server '$last_name'"
        exit 0
    fi
    echo "Last known server not responding, trying other servers..."
fi

# Try each server in the configuration
jq -r '.servers | to_entries[] | "\(.key)|\(.value)"' "$CONFIG_FILE" | while IFS='|' read -r name ip; do
    if test_server "$name" "$ip"; then
        found_server=true
        echo "Found active server: '$name'"
        break
    fi
done

if [ "$found_server" = false ]; then
    echo "No active servers found."
    echo "Please ensure that:"
    echo "1. The server is running"
    echo "2. The server is configured to listen on external interfaces (0.0.0.0)"
    echo "3. Any firewall rules allow incoming connections on port $PORT"
    exit 1
fi
