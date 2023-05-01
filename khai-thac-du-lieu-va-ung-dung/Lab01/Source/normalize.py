import argparse
from functions import normalize
#python normalize.py house-prices.csv --method=min-max --columns LotFrontage MasVnrArea --out=result.csv
#python normalize.py house-prices.csv --method=z-score --columns LotFrontage MasVnrArea --out=result.csv
parser = argparse.ArgumentParser(description='Thêm dữ liệu bị thiếu vào bộ dữ liệu')

parser.add_argument('file_path', help='Đường dẫn đến tập tin input')
parser.add_argument('--columns', nargs='+', help='chọn cột để chuẩn hoá', required=True)
parser.add_argument('--method', choices=['min-max', 'z-score'], default='min-max', help='phương pháp chuẩn hoá')
parser.add_argument('--out', help='Đường dẫn đến tập tin output')

args = parser.parse_args()

print(normalize(args)[args.columns])
