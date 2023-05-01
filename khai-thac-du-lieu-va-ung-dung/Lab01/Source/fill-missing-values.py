import argparse
from functions import fill_mising_values
#python fill-missing-values.py house-prices.csv --method=mean --columns LotFrontage MasVnrArea --out=result.csv
#python fill-missing-values.py house-prices.csv --method=median --columns GarageYrBlt --out=result.csv
#python fill-missing-values.py house-prices.csv --method=mode --columns BsmtQual BsmtFinType1 --out=result.csv

parser = argparse.ArgumentParser(description='Thêm dữ liệu bị thiếu vào bộ dữ liệu')

parser.add_argument('file_path', help='Đường dẫn đến tập tin input')
parser.add_argument('--columns', nargs='+', help='chọn cột để thêm dữ liệu', required=True)
parser.add_argument('--method', choices=['mean', 'median', 'mode'], default='mode', help='phương pháp thêm dữ liệu bị mất')
parser.add_argument('--out', help='Đường dẫn đến tập tin output')

args = parser.parse_args()

fill_mising_values(args)