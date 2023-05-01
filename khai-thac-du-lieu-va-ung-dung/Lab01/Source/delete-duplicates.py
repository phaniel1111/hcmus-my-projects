import argparse
from functions import delete_duplicates
#python delete-duplicates.py house-prices.csv --out=result.csv

parser = argparse.ArgumentParser(description='Xóa các hàng bị thiếu dữ liệu trong file')
parser.add_argument('file_path', help='Đường dẫn đến tập tin input')
parser.add_argument('--out', help='Đường dẫn đến tập tin output')

args = parser.parse_args()

delete_duplicates(args)
