import argparse
from functions import count_mising_lines
#python count-missing-lines.py house-prices.csv

parser = argparse.ArgumentParser(description='Đếm số dòng thiếu giá trị')
parser.add_argument('file_path', type=str, help='Đường dẫn đến tập tin input')
args = parser.parse_args()

print('Tổng số dòng bị thiếu dữ liệu tập tin:', str(count_mising_lines(args.file_path)))