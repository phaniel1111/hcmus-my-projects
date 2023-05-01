import argparse
from functions import missing_columns
#python missing-columns.py house-prices.csv

parser = argparse.ArgumentParser(description='Trích xuất các cột bị thiếu giá trị')
parser.add_argument('file_path', type=str, help='Đường dẫn đến tập tin input')
args = parser.parse_args()

print('Các cột bị thiếu dữ liệu trong tập tin:')
for k,v in missing_columns(args.file_path).items():
    print(k,": ",str(v))