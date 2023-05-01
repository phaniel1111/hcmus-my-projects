import argparse
from functions import delete_missing_rows
#python delete-missing-rows.py house-prices.csv --percentage 10 --out=result.csv

parser = argparse.ArgumentParser(description='Xóa các hàng bị thiếu dữ liệu trong file')
parser.add_argument('file_path', help='Đường dẫn đến tập tin input')
parser.add_argument('--percentage', type=int, default=50, help='Phần trăm giá trị tối thiểu để loại bỏ hàng')
parser.add_argument('--out', help='Đường dẫn đến tập tin output')

args = parser.parse_args()

delete_missing_rows(args)
