#!/bin/bash

# Array of potential IP addresses where the server might be running
declare -a server_ips=(
    "localhost"
    "127.0.0.1"
    "172.18.148.67"  # Your main IP
    "172.17.0.1"     # Your secondary IP
    "172.18.148.66"  # Adjacent IP in case of DHCP reassignment
    "172.18.148.68"  # Adjacent IP in case of DHCP reassignment
    "172.17.0.2"     # Common Docker container IP
    "172.17.0.3"     # Common Docker container IP
)

# The port where your server is running
PORT=8080

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
    if [[ "$ip" == "localhost" || "$ip" == "127.0.0.1" ]]; then
        return 0  # Skip ping for localhost
    fi
    ping -c 1 -W 1 "$ip" >/dev/null 2>&1
    return $?
}

# Function to test a single server
test_server() {
    local ip=$1
    echo "Testing server at $ip:$PORT..."
    
    # Check if IP is reachable first (skip for localhost)
    if ! check_ping "$ip"; then
        echo "✗ Host $ip is not reachable"
        return 1
    fi
    
    # Use curl with a 2-second timeout
    response=$(curl -s -X POST "http://$ip:$PORT/api/v1/pricing/black-scholes" \
        -H "Content-Type: application/json" \
        -d "$JSON_DATA" \
        --connect-timeout 2)
    
    if [ $? -eq 0 ] && [ ! -z "$response" ]; then
        echo "✓ Server found and responding at $ip:$PORT"
        echo "Response: $response"
        # Save the working IP to a temporary file for future use
        echo "$ip" > /tmp/last_working_server
        return 0
    else
        echo "✗ No server response at $ip:$PORT"
        return 1
    fi
}

# Main script
echo "Starting server discovery..."
echo "Timestamp: $(date)"
found_server=false

# If we have a last working server, try it first
if [ -f /tmp/last_working_server ]; then
    last_ip=$(cat /tmp/last_working_server)
    echo "Trying last known working server at $last_ip first..."
    if test_server "$last_ip"; then
        found_server=true
        echo "Successfully connected to last known server at $last_ip:$PORT"
        exit 0
    fi
    echo "Last known server not responding, trying other addresses..."
fi

for ip in "${server_ips[@]}"; do
    if test_server "$ip"; then
        found_server=true
        echo "Found active server at $ip:$PORT"
        break
    fi
done

if [ "$found_server" = false ]; then
    echo "No active servers found on any of the specified addresses."
    echo "Please ensure that:"
    echo "1. The server is running"
    echo "2. The server is configured to listen on external interfaces (0.0.0.0)"
    echo "3. Any firewall rules allow incoming connections on port $PORT"
    exit 1
fi
