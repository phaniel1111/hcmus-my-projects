CẤU TRÚC THƯ MỤC SOURCE

|Source
	|---DC (thư mục chứa source ví dụ Differential cryptanalysis)
	|---RSA (thư mục chứa source chương trình mã hoá tập tin)
	|---Input (thư mục chứa đầu vào mẫu chương trình mã hoá tập tin)
		|---plaintext.txt (Tập tin Plaintext mẫu)
		|---RSA64Bits.txt (Khoá 64 bit)
		|---RSA512Bits.txt (Khoá 512 bit)
		|---RSA1024Bits.txt (Khoá 1024 bit)
	|---RSA.exe (Tập tin thực thi chương trình mã hoá tập tin)
	|---DC.exe (Tập tin thực thi ví dụ Differential cryptanalysis)
	|---README.txt (Tập tin này)

------

CÁCH SỬ DỤNG CHƯƠNG TRÌNH MÃ HOÁ TẬP TIN


Bước 1: Truy cập vào file RSA.exe trong thư mục này.

Bước 2: Giao diện chương trình có 6 chức năng sau: tự nhập khoá, sinh khoá RSA, xem khoá, mã hoá tập tin, Giải mã tập tin, thoát chương trình.

Bước 3: Nhập chức năng muốn thực hiện và làm theo hướng dẫn. Các chức năng gồm:
		1. Tự nhập khoá: Người dùng có thể tìm thấy khoá công khai, khoá bí mật và modulo ở thư mục Input. Lần lược nhập theo thứ tự khoá công khai -> khoá bí mật -> modulo.
		2. Chương trình tự tạo khoá: Người dùng chọn độ dài khoá cần tạo (512,1024,2048 bit) và đợi sinh khoá.
		3. Xem khoá: In khoá ra màn hình.
		4. Mã hoá: Người dùng nhập đường dẫn đến file PLAINTEXT.txt (vd. D:\plaintext.txt) và file CIPHERTEXT.txt (vd. D:\ciphertext.txt) và đợi chương trình mã hoá.
		5. Giải mã: Người dùng nhập đường dẫn đến file CIPHERTEXT.txt (vd. D:\ciphertext.txt) và file PLAINTEXT.txt (vd. D:\plaintext1.txt) và và đợi chương trình giải mã.
		0. Thoát chương trình.

Bước 4: Người dùng sẽ được yêu cầu nhập 0 để thoát chương trình. Hoặc nhập số bất kì để tiếp tục chức năng khác

------

CÁCH TÌM SOURCE CODE CỦA CHƯƠNG TRÌNH MÃ HOÁ TẬP TIN

Từ thư mục này, người dùng chọn thư mục RSA -> RSA. Ở đây sẽ có các tập tin c++ chứa source của chương trình.

------

CÁCH CHẠY CHƯƠNG TRÌNH MÔ PHỎNG Differential cryptanalysis

Truy cập vào file DC.exe trong thư mục này.

------

CÁCH TÌM SOURCE CODE CỦA CHƯƠNG TRÌNH MÔ PHỎNG Differential cryptanalysis

Từ thư mục này, người dùng chọn thư mục DC -> DC. Ở đây sẽ có tập tin Source,cpp chứa source của chương trình.
