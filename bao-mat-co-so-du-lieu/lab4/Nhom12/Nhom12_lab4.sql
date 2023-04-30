﻿USE master
GO
IF DB_ID('QLSVNhom') IS NOT NULL
	DROP DATABASE QLSVNhom
GO
CREATE DATABASE QLSVNhom
GO
USE QLSVNhom
GO
-- Tạo bảng
CREATE TABLE SINHVIEN(
	MASV VARCHAR(20) NOT NULL,
	HOTEN NVARCHAR(100) NOT NULL,
	NGAYSINH DATETIME,
	DIACHI NVARCHAR(200),
	MALOP VARCHAR(20),
	TENDN NVARCHAR(100) NOT NULL,
	MATKHAU VARBINARY(MAX) NOT NULL,
	PRIMARY KEY(MASV)
	)
GO
CREATE TABLE NHANVIEN(
	MANV VARCHAR(20) NOT NULL,
	HOTEN NVARCHAR(100) NOT NULL,
	EMAIL VARCHAR(20),
	LUONG VARBINARY(MAX),
	TENDN NVARCHAR(100) NOT NULL,
	MATKHAU VARBINARY(MAX) NOT NULL,
	PUBKEY VARCHAR(MAX),
	PRIMARY KEY(MANV)
	)
GO
CREATE TABLE LOP(
	MALOP VARCHAR(20) NOT NULL,
	TENLOP NVARCHAR(100) NOT NULL,
	MANV VARCHAR(20),
	PRIMARY KEY(MALOP)
	)
GO
CREATE TABLE HOCPHAN(
	MAHP VARCHAR(20) NOT NULL,
	TENHP NVARCHAR(100) NOT NULL,
	SOTC INT,
	PRIMARY KEY(MAHP)
	)
GO
CREATE TABLE BANGDIEM(
	MASV VARCHAR(20) NOT NULL,
	MAHP VARCHAR(20) NOT NULL,
	DIEMTHI VARBINARY(MAX),
	PRIMARY KEY(MAHP,MASV)
	)
GO
-- TẠO KHOÁ NGOẠI
ALTER TABLE SINHVIEN ADD CONSTRAINT FK_SINHVIEN_LOP FOREIGN KEY (MALOP) REFERENCES LOP (MALOP);
GO
ALTER TABLE LOP ADD CONSTRAINT FK_LOP_NHANVIEN FOREIGN KEY (MANV) REFERENCES NHANVIEN (MANV);
GO
ALTER TABLE BANGDIEM ADD CONSTRAINT FK_BANGDIEM_SINHVIEN FOREIGN KEY (MASV) REFERENCES SINHVIEN (MASV);
GO
ALTER TABLE BANGDIEM ADD CONSTRAINT FK_BANGDIEM_HOCPHAN FOREIGN KEY (MAHP) REFERENCES HOCPHAN (MAHP);
GO
-- Câu i
IF OBJECT_ID('SP_INS_PUBLIC_ENCRYPT_NHANVIEN','P') IS NOT NULL
DROP PROCEDURE SP_INS_PUBLIC_ENCRYPT_NHANVIEN
GO
CREATE PROCEDURE SP_INS_PUBLIC_ENCRYPT_NHANVIEN
	@MANV VARCHAR(20),
	@HOTEN NVARCHAR(100),
	@EMAIL VARCHAR(20),
	@LUONG varbinary(max),
	@TENDN NVARCHAR(100),
	@MATKHAU varbinary(max),
	@PUBKEY varchar(MAX)
AS
BEGIN
    INSERT INTO NHANVIEN (MANV, HOTEN, EMAIL, LUONG, TENDN, MATKHAU,PUBKEY)
    VALUES (@MANV, @HOTEN, @EMAIL,  @LUONG, @TENDN, @MATKHAU, @PUBKEY);
END
GO
-- Câu ii
IF OBJECT_ID('SP_SEL_PUBLIC_ENCRYPT_NHANVIEN','P') IS NOT NULL
DROP PROCEDURE SP_SEL_PUBLIC_ENCRYPT_NHANVIEN
GO
CREATE PROCEDURE SP_SEL_PUBLIC_ENCRYPT_NHANVIEN
	@MANV NVARCHAR(100),
	@MATKHAU varbinary(max)
AS
BEGIN
	SELECT NV.MANV, NV.HOTEN, NV.EMAIL, NV.LUONG
	FROM NHANVIEN AS NV
	where nv.TENDN = @MANV and NV.MATKHAU = @MATKHAU
END
GO 
-- Dành cho ứng dụng

-- Màn hình đăng nhập
IF OBJECT_ID('SP_SEL_LOG_IN','P') IS NOT NULL
DROP PROCEDURE SP_SEL_LOG_IN
GO
CREATE PROCEDURE SP_SEL_LOG_IN
	@TENDN NVARCHAR(100),
	@MATKHAU varbinary(max)
AS
BEGIN
	SELECT NV.MANV
	FROM NHANVIEN AS NV
	where  nv.TENDN = @TENDN and NV.MATKHAU = @MATKHAU
END
GO 
-- Xem bảng nhân viên
IF OBJECT_ID('SP_SEL_NHANVIEN','P') IS NOT NULL
DROP PROCEDURE SP_SEL_NHANVIEN
GO
CREATE PROCEDURE SP_SEL_NHANVIEN
AS
BEGIN
	SELECT NV.MANV, NV.HOTEN, NV.EMAIL, NV.LUONG, NV.PUBKEY
	FROM NHANVIEN AS NV
END
GO 
-- Cập nhật nhân viên
IF OBJECT_ID('SP_UPD_PUBLIC_ENCRYPT_NHANVIEN','P') IS NOT NULL
DROP PROCEDURE SP_UPD_PUBLIC_ENCRYPT_NHANVIEN
GO
CREATE PROCEDURE SP_UPD_PUBLIC_ENCRYPT_NHANVIEN
	@MANV VARCHAR(20),
	@HOTEN NVARCHAR(100),
	@EMAIL VARCHAR(20),
	@LUONG varbinary(max),
	@TENDN NVARCHAR(100),
	@MATKHAU varbinary(max)
AS
BEGIN
    UPDATE NHANVIEN
    set HOTEN = @HOTEN, EMAIL = @EMAIL, LUONG =  @LUONG, TENDN = @TENDN, MATKHAU = @MATKHAU
	where MANV = @MANV
END
GO
--Stored procedure xóa lớp

CREATE PROCEDURE SP_DELETE_CLASS(
	@MALOP VARCHAR(20),
	@TENLOP NVARCHAR(100),
	@MANV VARCHAR(20)
	)
AS
BEGIN
	if (select COUNT(*) from LOP where MALOP=@MALOP and TENLOP=@TENLOP and MANV=@MANV)>0 
	begin
	update SINHVIEN set MALOP=null where MALOP= @MALOP
	delete LOP where MALOP=@MALOP
	end
	else
	print('Error')
END
-- update sinh vien
GO
CREATE PROCEDURE SP_UPDATE_SV
	@MASV VARCHAR(20),
	@HOTEN NVARCHAR(100),
	@NGAYSINH DATETIME,
	@DIACHI NVARCHAR(200),
	@MALOP VARCHAR(20)
AS
BEGIN
	UPDATE SINHVIEN
	SET MASV=@MASV,HOTEN=@HOTEN,NGAYSINH=@NGAYSINH,DIACHI=@DIACHI,MALOP=@MALOP
	WHERE MASV = @MASV;
END
GO
-- check nv quan ly sv--
GO
CREATE PROCEDURE SP_QL_SV
	@MANV VARCHAR(20),
	@MASV VARCHAR(20)
AS
BEGIN
	SELECT *
	FROM SINHVIEN as sv
	INNER JOIN lop ON sv.MALOP = lop.MALOP
	INNER JOIN NHANVIEN as nv ON lop.MANV = nv.MANV
	where sv.MASV = @MASV and nv.MANV = @MANV
END
GO
-- Thêm điểm
IF OBJECT_ID('SP_INS_PUBLIC_ENCRYPT_BANGDIEM','P') IS NOT NULL
DROP PROCEDURE SP_INS_PUBLIC_ENCRYPT_BANGDIEM
GO
CREATE PROCEDURE SP_INS_PUBLIC_ENCRYPT_BANGDIEM
	@MASV VARCHAR(20),
	@MAHP VARCHAR(20),
	@DIEMTHI varbinary(max)
AS
BEGIN
    INSERT INTO BANGDIEM (MASV, MAHP, DIEMTHI)
    VALUES (@MASV, @MAHP, @DIEMTHI);
END
GO
--Xem điểm
IF OBJECT_ID('SP_SEL_PUBLIC_ENCRYPT_BANGDIEM','P') IS NOT NULL
DROP PROCEDURE SP_SEL_PUBLIC_ENCRYPT_BANGDIEM
GO
CREATE PROCEDURE SP_SEL_PUBLIC_ENCRYPT_BANGDIEM
AS
BEGIN
    SELECT D.MASV, D.MAHP, D.DIEMTHI 
	FROM BANGDIEM AS D
END
GO
exec SP_SEL_PUBLIC_ENCRYPT_BANGDIEM
---

--- Dữ liệu mẫu

declare @p VARBINARY(MAX)
set @p = 0xFB398CC690E15DDBA43EE811B6C0D3EC190901AD3DF377FEC9A1F9004B919A06
declare @l1 VARBINARY(MAX)
set @l1 = 0x4C55CF49221A104EBBF7DB371A595B58B7DD4B0F5DF9DF847EA786EA4FB98A191DDAC2123AF9FB9555E735C9C23104E78E3478E405861B07E45BE30F4D4C6AA34C2B4403F81BEBF4346857637712F3B5629D11F7320169E3C735C0A39B81DC2BEFA0CD07E66886FB18A89DA1AD2AC0E95709790309D47F82269737B2822EBEB6
declare @l2 VARBINARY(MAX)
set @l2 = 0x4C96D16D7E2948C11FD91961D7DE0160654D0AE23C1914E09355F5B9DB984B81997DA2862EB29FAF27FFBA5E24E0735DEF2644AEFD70701BDB9BCED8F8170F5A37DD32A6F72F9EB1E65861228A7639FB7CEFC4BF0E6657A5EBDC944061863D9290E451210286A8F07CEE75D55185EA7F02A71DBE60B80054B2BB3B335845C47D
declare @k1 varchar(max)
set @k1 = '3M/1oMYt3U2kk+T8+eu5dezwcrSAPPq/9NjnO5148q0rPFhg5VaS0G89VC50E4Ebv6MK4vgZ7WcWAiDm31oVCMUA2DafUwO34RUumxqiRXl9lS8Wc6fbi7aRCfcSJfxL+bEre8F7ClgNjdARFBZw1RZ4uL7kIp3OGDiLsqIVVEk=;AQAB'
declare @k2 varchar(max)
set @k2 = '38HRX3boONsvf6Ls9JG+72J4uZukgkOEJkz9wQa5ckCtJFXh/fKg/ntB+s3vC0dtRNIHCdhU3eGzX/LFTQBGeMLLn6kg+vR7z3xsRC5KI8I+nYybqQoXaB7sXL2YdZg44qswHz/4ELnWM8t2K76SoSq7C/dAfAfrWJUz4ZuTwzU=;AQAB'
EXEC SP_INS_PUBLIC_ENCRYPT_NHANVIEN 'NV01', 'NGUYEN VAN A', 'NVA@',@l1, 'NVA', @p, @k1
EXEC SP_INS_PUBLIC_ENCRYPT_NHANVIEN 'NV02', 'NGUYEN VAN B', 'NVB@',@l2, 'NVB', @p, @k2

INSERT INTO LOP(MALOP,TENLOP,MANV)
VALUES 
	('L01', N'Công nghệ thông tin K20','NV01'),
	('L02', N'Công nghệ thông tin K21','NV02')
GO

INSERT INTO HOCPHAN(MAHP,TENHP,SOTC)
VALUES 
	('HP01', N'Nhập môn mã hoá mật mã',4),
	('HP02', N'Mã hoá cơ sở dữ liệu',4)
GO

declare @b VARBINARY(MAX) 
set @b = 0xFB398CC690E15DDBA43EE811B6C0D3EC190901AD3DF377FEC9A1F9004B919A06
INSERT INTO SINHVIEN(MASV,HOTEN,NGAYSINH,DIACHI,MALOP,TENDN,MATKHAU)
VALUES 
	('SV01', N'Trần Văn C','2002-01-01', N'280 AN DUONG VUONG', 'L01', N'SVC', @b),
	('SV02', N'Trần Văn D','2002-01-01', N'280 TO VINH DIEN', 'L01', N'SVD', @b),
	('SV03', N'Trần Văn E','2002-01-01', N'280 AN DUONG VUONG', 'L02', N'SVE', @b),
	('SV04', N'Trần Văn F','2002-01-01', N'280 TO VINH DIEN', 'L02', N'SVF', @b)
GO

declare @d1 VARBINARY(MAX) 
declare @d2 VARBINARY(MAX) 
set @d1 = 0xDC5A5A3353860559C8BD9885D3B7A0872079DE31097FE4BD3A376F242D92C4B71A20AA895DB60A856934ECA33C6468E6253BD007031B1729F966F3902B497F834A492EA7CCAF0AC4346ED15AC55AB46DE064115E8F660DFC05A70BD4938FF5CC7831E94BA522BE5111048433CF8987B78757046649D32B993DE223095422289A
set @d2 = 0x1C3C619DA5B9C805D16375086A0A9CCF315F1994ADBF36DC00BF468B6457836D9790B08806B659B0BA06FC410BA08839051C758488F51CDA51CBF8671439CE00E46C8B89E5748B7867E5AC724FAC45B08D762834F7CD6BE6ED2D74647F411F42E80CFA1B0197A620E8C9767836B9D30096502A3C96C66847687445F4D3E18D12
INSERT INTO BANGDIEM (MASV, MAHP, DIEMTHI)
VALUES 
	('SV01', 'HP01', @d1),
	('SV02','HP02', @d2)
GO
