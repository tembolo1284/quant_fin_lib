from quant_fin import black_scholes_price

def test_black_scholes_call():
    price = black_scholes_price(100, 100, 0.05, 1, 0.2, 1)
    assert abs(price - 10.45) < 0.01

def test_black_scholes_put():
    price = black_scholes_price(100, 100, 0.05, 1, 0.2, 0)
    assert abs(price - 5.57) < 0.01

