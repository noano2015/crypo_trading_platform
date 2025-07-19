import random
import datetime
import csv
from io import StringIO

def generate_trading_data():
    # Starting parameters based on your sample data
    start_date = datetime.datetime(2020, 3, 17, 17, 1, 24, 884492)
    end_date = start_date + datetime.timedelta(weeks=150)
    
    # Trading pairs and their base prices from your sample data
    trading_pairs = {
        'ETH/BTC': {
            'base_price': 0.02187,
            'price_decimals': 8,
            'amount_range': (0.001, 200),
            'large_order_range': (10, 300)
        },
        'DOGE/BTC': {
            'base_price': 0.0000003,
            'price_decimals': 8,
            'amount_range': (1000000, 80000000),
            'large_order_range': (30000000, 100000000)
        },
        'BTC/USDT': {
            'base_price': 5348.75,
            'price_decimals': 8,
            'amount_range': (0.001, 10),
            'large_order_range': (5, 50)
        },
        'ETH/USDT': {
            'base_price': 116.0,
            'price_decimals': 8,
            'amount_range': (0.01, 500),
            'large_order_range': (100, 1000)
        },
        'DOGE/USDT': {
            'base_price': 0.00163,
            'price_decimals': 8,
            'amount_range': (1000, 800000),
            'large_order_range': (200000, 1000000)
        }
    }
    
    # Price volatility parameters
    daily_volatility = 0.15  # 15% daily volatility (increased from 5%)
    trend_factor = 0.0001   # Small upward trend over time
    volatility_spikes = True  # Enable occasional volatility spikes
    
    data = []
    current_time = start_date
    
    # Initialize current prices for each pair
    current_prices = {pair: config['base_price'] for pair, config in trading_pairs.items()}
    
    # Generate approximately 300,000 records over 150 weeks
    # Distribute across all trading pairs
    total_records = 300000
    time_increment_seconds = (end_date - start_date).total_seconds() / total_records
    
    for i in range(total_records):
        # Select random trading pair
        pair = random.choice(list(trading_pairs.keys()))
        pair_config = trading_pairs[pair]
        
        # Update time
        current_time += datetime.timedelta(seconds=time_increment_seconds)
        
        # Price evolution with random walk and trend
        current_price = current_prices[pair]
        
        # Base volatility (adjust based on price level)
        if pair in ['BTC/USDT', 'ETH/USDT']:
            daily_volatility = 0.12  # Slightly lower volatility for USDT pairs
        else:
            daily_volatility = 0.15  # Higher volatility for BTC pairs and DOGE
        
        base_volatility = daily_volatility * current_price / (24 * 60 * 60) ** 0.5
        
        # Add occasional volatility spikes (market events)
        if volatility_spikes and random.random() < 0.0001:  # 0.01% chance per record
            spike_multiplier = random.uniform(3, 8)  # 3-8x normal volatility
            base_volatility *= spike_multiplier
        
        # Add momentum effect (trending moves)
        if i > 100:  # After first 100 records
            # Calculate momentum based on this pair's history
            pair_history = [record for record in data[-100:] if record[1] == pair]
            if len(pair_history) > 10:
                recent_change = (current_price - pair_history[-10][3]) / current_price
                momentum = recent_change * 0.3  # 30% momentum effect
            else:
                momentum = 0
        else:
            momentum = 0
        
        # Calculate price change with enhanced volatility
        price_change = random.gauss(momentum, base_volatility)
        
        # Add some mean reversion (price tends to return to base over time)
        base_price = pair_config['base_price']
        mean_reversion = (base_price - current_price) * 0.00001
        
        current_price += price_change + trend_factor * current_price / total_records + mean_reversion
        
        # Ensure price doesn't go negative or too extreme
        min_price = base_price * 0.1  # Don't go below 10% of base
        max_price = base_price * 10   # Don't go above 10x base
        current_price = max(min_price, min(max_price, current_price))
        
        # Update the current price for this pair
        current_prices[pair] = current_price
        
        # Generate bid/ask spread (wider during high volatility)
        base_spread_percent = random.uniform(0.0001, 0.001)
        
        # Increase spread during high volatility periods
        if abs(price_change) > base_volatility * 2:
            spread_multiplier = random.uniform(1.5, 3.0)
            base_spread_percent *= spread_multiplier
        
        spread = current_price * base_spread_percent
        
        # Determine if this is a bid or ask
        order_type = random.choice(['bid', 'ask'])
        
        if order_type == 'bid':
            # Bid price is slightly below current price
            price = current_price - spread/2 + random.gauss(0, spread/3)
        else:
            # Ask price is slightly above current price  
            price = current_price + spread/2 + random.gauss(0, spread/3)
        
        # Ensure price is positive and reasonable
        price = max(0.001, price)
        
        # Generate realistic amount (volume) based on pair type
        volume_multiplier = 1.0
        if abs(price_change) > base_volatility * 1.5:
            volume_multiplier = random.uniform(1.5, 4.0)  # Higher volume during price movements
        
        # Different volume ranges for different pairs
        amount_range = pair_config['amount_range']
        large_order_range = pair_config['large_order_range']
        
        # Mix of small and large orders
        if random.random() < 0.12:  # 12% chance of large order
            amount = random.uniform(large_order_range[0], large_order_range[1]) * volume_multiplier
        else:
            amount = random.uniform(amount_range[0], amount_range[1]) * volume_multiplier
        
        # Round price to appropriate decimal places
        price = round(current_price, pair_config['price_decimals'])
        
        # Format timestamp to match your sample
        timestamp_str = current_time.strftime("%Y/%m/%d %H:%M:%S.%f")
        
        # Add some microsecond variation
        if random.random() < 0.3:  # 30% chance to vary microseconds
            microseconds = random.randint(100000, 999999)
            timestamp_parts = timestamp_str.split('.')
            timestamp_str = f"{timestamp_parts[0]}.{microseconds}"
        
        record = [timestamp_str, pair, order_type, price, amount]
        data.append(record)
        
        # Occasionally add multiple orders at the same timestamp (like your sample)
        if random.random() < 0.05:  # 5% chance
            num_same_time = random.randint(2, 5)
            for _ in range(num_same_time):
                same_time_type = random.choice(['bid', 'ask'])
                if same_time_type == 'bid':
                    same_price = price - random.uniform(0.0001 * price, 0.01 * price)
                else:
                    same_price = price + random.uniform(0.0001 * price, 0.01 * price)
                
                same_price = max(min_price, round(same_price, pair_config['price_decimals']))
                
                # Same time orders with different amounts
                if random.random() < 0.1:
                    same_amount = random.uniform(large_order_range[0], large_order_range[1])
                else:
                    same_amount = random.uniform(amount_range[0], amount_range[1])
                
                same_record = [timestamp_str, pair, same_time_type, same_price, same_amount]
                data.append(same_record)
    
    return data

# Generate the data
print("Generating trading data...")
trading_data = generate_trading_data()

# Sort by timestamp to ensure chronological order
trading_data.sort(key=lambda x: x[0])

print(f"Generated {len(trading_data)} records")
print(f"Time range: {trading_data[0][0]} to {trading_data[-1][0]}")
print(f"Price range: {min(row[3] for row in trading_data):.8f} to {max(row[3] for row in trading_data):.8f}")

# Create CSV content
csv_content = StringIO()
writer = csv.writer(csv_content)
writer.writerows(trading_data)

# Display first few rows as sample
print("\nFirst 10 rows:")
for i, row in enumerate(trading_data[:10]):
    print(f"{row[0]},{row[1]},{row[2]},{row[3]},{row[4]}")

print(f"\nLast 5 rows:")
for row in trading_data[-5:]:
    print(f"{row[0]},{row[1]},{row[2]},{row[3]},{row[4]}")

# Show statistics
bid_count = sum(1 for row in trading_data if row[2] == 'bid')
ask_count = sum(1 for row in trading_data if row[2] == 'ask')
print(f"\nStatistics:")
print(f"Total records: {len(trading_data)}")
print(f"Bid orders: {bid_count}")
print(f"Ask orders: {ask_count}")
print(f"Average price: {sum(row[3] for row in trading_data) / len(trading_data):.8f}")

# Save to file (you can copy this content to a CSV file)
print(f"\n--- CSV DATA STARTS HERE ---")
print(csv_content.getvalue())