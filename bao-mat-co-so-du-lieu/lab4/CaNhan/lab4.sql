﻿/*----------------------------------------------------------
MASV: 20120313
HO TEN: Phan Tan Kiet
LAB: 04
NGAY: 27/04/2023
----------------------------------------------------------*/
USE master
GO
IF DB_ID('QLSV') IS NOT NULL
	DROP DATABASE QLSV
GO
CREATE DATABASE QLSV
GO
USE QLSV
GO
-- CREATE TABLES
CREATE TABLE SINHVIEN(
	MASV NVARCHAR(20) NOT NULL,
	HOTEN NVARCHAR(100) NOT NULL,
	NGAYSINH DATETIME,
	DIACHI NVARCHAR(200),
	MALOP VARCHAR(20),
	TENDN NVARCHAR(100) NOT NULL,
	MATKHAU VARBINARY(100) NOT NULL,
	PRIMARY KEY(MASV)
	)
GO
CREATE TABLE NHANVIEN(
	MANV VARCHAR(20) NOT NULL,
	HOTEN NVARCHAR(100) NOT NULL,
	EMAIL VARCHAR(20),
	LUONG VARBINARY(100),
	TENDN NVARCHAR(100) NOT NULL,
	MATKHAU VARBINARY(100) NOT NULL,
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
-- Câu c: i:
IF OBJECT_ID('dbo.SP_INS_ENCRYPT_SINHVIEN','P') IS NOT NULL
DROP PROCEDURE dbo.SP_INS_ENCRYPT_SINHVIEN
GO
CREATE PROCEDURE dbo.SP_INS_ENCRYPT_SINHVIEN
	@MASV NVARCHAR(20),
	@HOTEN NVARCHAR(100),
	@NGAYSINH DATETIME,
	@DIACHI NVARCHAR(200),
	@MALOP VARCHAR(20),
	@TENDN NVARCHAR(100),
	@MATKHAU varbinary
AS
BEGIN
	INSERT INTO SINHVIEN(MASV, HOTEN, NGAYSINH, DIACHI, MALOP, TENDN, MATKHAU)
	VALUES (@MASV, @HOTEN, @NGAYSINH, @DIACHI, @MALOP, @TENDN, @MATKHAU)
END
GO
-- ii
IF OBJECT_ID('SP_INS_ENCRYPT_NHANVIEN','P') IS NOT NULL
DROP PROCEDURE SP_INS_ENCRYPT_NHANVIEN
GO
CREATE PROCEDURE SP_INS_ENCRYPT_NHANVIEN
	@MANV VARCHAR(20),
	@HOTEN NVARCHAR(100),
	@EMAIL VARCHAR(20),
	@LUONG varbinary(max),
	@TENDN NVARCHAR(100),
	@MATKHAU varbinary(max)
AS
BEGIN
    INSERT INTO NHANVIEN (MANV, HOTEN, EMAIL, LUONG, TENDN, MATKHAU)
    VALUES (@MANV, @HOTEN, @EMAIL,  @LUONG, @TENDN, @MATKHAU);
END
GO
-- iii
IF OBJECT_ID('SP_SEL_ENCRYPT_NHANVIEN','P') IS NOT NULL
DROP PROCEDURE SP_SEL_ENCRYPT_NHANVIEN
GO
CREATE PROCEDURE SP_SEL_ENCRYPT_NHANVIEN
AS
BEGIN
	SELECT NV.MANV, NV.HOTEN, NV.EMAIL,NV.LUONG as LUONG
	FROM NHANVIEN AS NV
END
GO 

-- Chuc nang chinh sua nhan vien
IF OBJECT_ID('SP_UPD_ENCRYPT_NHANVIEN','P') IS NOT NULL
DROP PROCEDURE SP_UPD_ENCRYPT_NHANVIEN
GO
CREATE PROCEDURE SP_UPD_ENCRYPT_NHANVIEN
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
-- THem nhanvien
declare @p VARBINARY(MAX)  
declare @l VARBINARY(MAX)   
set @p = 0xFB398CC690E15DDBA43EE811B6C0D3EC190901AD3DF377FEC9A1F9004B919A06
set @l = 0x8BC65D42D5CBA6ACFE41F74BFEECD67B
exec SP_INS_ENCRYPT_NHANVIEN 'NV01', 'NGUYEN VAN A', 'NVA@',@l, 'NVA', @p

--- THực thi câu lệnh
-- câu f
-- exec sp_executesql N'SELECT NV.MANV, NV.TENDN FROM NHANVIEN AS NV where nv.TENDN = @username and NV.MATKHAU = @password',N'@username nvarchar(3),@password varbinary(32)',@username=N'NVA',@password=0xFB398CC690E15DDBA43EE811B6C0D3EC190901AD3DF377FEC9A1F9004B919A06
declare @p VARBINARY(MAX)  
declare @u NVARCHAR(100)  
set @p = 0xFB398CC690E15DDBA43EE811B6C0D3EC190901AD3DF377FEC9A1F9004B919A06
set @u = N'NVA'
SELECT NV.MANV, NV.TENDN FROM NHANVIEN AS NV 
where nv.TENDN = @u and NV.MATKHAU = @p

