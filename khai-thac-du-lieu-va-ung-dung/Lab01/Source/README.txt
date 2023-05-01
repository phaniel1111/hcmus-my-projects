Thư mục Source chứa 11 tập tin, trong đó bao gồm :
•	Tập tin functions.py : chứa 8 hàm tiền xử lý dữ liệu
•	Tập tin house-prices.csv: bộ dư liệu được cung cấp
•	Tập tin README.txt: thông tin và hướng dẫn cách sử dụng các hàm
•	8 tập tin còn lại tương ứng với 8 yêu cầu của đề, mỗi tập tin sẽ gọi 1 hàm từ functions.py, dùng command line để chạy các tập tin này.

Các lệnh test
1. Trích xuất các cột bị thiếu giá trị
    python missing-columns.py house-prices.csv
2. Đếm số dòng bị thiếu dữ liệu
    python count-missing-lines.py house-prices.csv
3. Điền vào giá trị còn thiếu.
    •	python fill-missing-values.py house-prices.csv --method=mean --columns LotFrontage MasVnrArea --out=result.csv
    •	python fill-missing-values.py house-prices.csv --method=median --columns GarageYrBlt --out=result.csv
    •	python fill-missing-values.py house-prices.csv --method=mode --columns BsmtQual BsmtFinType1 --out=result.csv
4. Xóa các hàng chứa nhiều hơn một số giá trị cụ thể bị thiếu
    python delete-missing-rows.py house-prices.csv --percentage 5 --out=result.csv
5. Xóa các cột chứa nhiều hơn một số giá trị cụ thể bị thiếu
    python delete-missing-columns.py house-prices.csv --percentage 10 --out=result.csv
6. Xóa các mẫu trùng lặp.
    python delete-duplicates.py house-prices.csv --out=result.csv
7. Chuẩn hóa thuộc tính số
    •	python normalize.py house-prices.csv --method=min-max --columns LotFrontage MasVnrArea --out=result.csv
    •	python normalize.py house-prices.csv --method=z-score --columns LotFrontage MasVnrArea --out=result.csv
8. Thực hiện cộng, trừ, nhân, chia hai thuộc tính số.
    •	python performing.py house-prices.csv --method=sum --columns LotFrontage MasVnrArea --newcolumn=sumColumns --out=result.csv
    •	python performing.py house-prices.csv --method=sum --columns LotFrontage MasVnrArea --newcolumn=subColumns --out=result.csv
    •	python performing.py house-prices.csv --method=sum --columns LotFrontage MasVnrArea --newcolumn=mulColumns --out=result.csv
    •	python performing.py house-prices.csv --method=sum --columns LotFrontage MasVnrArea --newcolumn=divColumns --out=result.csv



