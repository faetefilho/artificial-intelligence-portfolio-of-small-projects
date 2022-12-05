import json

def lambda_handler(event, context):
    
    count = event['stockunits']
    price = event['stockprice']
    
    total = count * price
    
    if event['currency'] == 'USD':
        return {'totalfunds': total}
    elif event['currency'] == 'CAD':
        return {'totalfunds': total * 1.3}