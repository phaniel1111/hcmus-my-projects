import argparse
from functions import performing
#python performing.py house-prices.csv --method=sum --columns LotFrontage MasVnrArea --newcolumn=sumColumns --out=result.csv
#python performing.py house-prices.csv --method=sum --columns LotFrontage MasVnrArea --newcolumn=subColumns --out=result.csv
#python performing.py house-prices.csv --method=sum --columns LotFrontage MasVnrArea --newcolumn=mulColumns --out=result.csv
#python performing.py house-prices.csv --method=sum --columns LotFrontage MasVnrArea --newcolumn=divColumns --out=result.csv


parser = argparse.ArgumentParser(description='Tính toán trên hai cột')

parser.add_argument('file_path', help='Đường dẫn đến tập tin input')
parser.add_argument('--columns', nargs=2, help='chọn cột để tính toán', required=True)
parser.add_argument('--method', choices=['sum', 'sub', 'mul', 'div'], default='sum', help='phương pháp tính toán')
parser.add_argument('--newcolumn', help='Tên của cột mới')
parser.add_argument('--out', help='Đường dẫn đến tập tin output')

args = parser.parse_args()

df = performing(args)

print(df[[args.columns[0],args.columns[1],args.newcolumn]])