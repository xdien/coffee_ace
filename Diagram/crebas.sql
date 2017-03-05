/*==============================================================*/
/* DBMS name:      MySQL 5.0                                    */
/* Created on:     3/1/2017 3:39:57 PM                          */
/*==============================================================*/


drop table if exists BAN;

drop table if exists CHI_TIET_PHIEU_XUAT;

drop table if exists HANG_HOA;

drop table if exists PHIEU_XUAT;

/*==============================================================*/
/* Table: BAN                                                   */
/*==============================================================*/
create table BAN
(
   BANID                varchar(12) not null,
   TEN                  national varchar(512),
   TRANG_THAI_TRONG     bool comment 'Tr?ng thái bàn',
   primary key (BANID)
);

/*==============================================================*/
/* Table: CHI_TIET_PHIEU_XUAT                                   */
/*==============================================================*/
create table CHI_TIET_PHIEU_XUAT
(
   PHIEUXUATID          varchar(12) not null,
   HANGHOAID            varchar(10) not null,
   SO_LUONG             int,
   CHIEC_KHAU           float,
   TONG_TIEN            int,
   TEN_HANG             national varchar(100),
   GIA_BAN_HIEN_TAI     int,
   DA_THANH_TOAN        bool comment 'Thuoc tinh kiem tra phie, bo qua neu phieu duoc tick la da thanh toan',
   primary key (PHIEUXUATID, HANGHOAID)
);

alter table CHI_TIET_PHIEU_XUAT comment 'Phòng khi khách yêu c?u';

/*==============================================================*/
/* Table: HANG_HOA                                              */
/*==============================================================*/
create table HANG_HOA
(
   HANGHOAID            varchar(10) not null,
   TEN                  national varchar(512),
   GIA_BAN              int,
   SL_TON               int,
   primary key (HANGHOAID)
);

/*==============================================================*/
/* Table: PHIEU_XUAT                                            */
/*==============================================================*/
create table PHIEU_XUAT
(
   PHIEUXUATID          varchar(12) not null,
   BANID                varchar(12) not null,
   CHIEC_KHAU           float,
   GIO_VAO              timestamp,
   GIO_RA               timestamp,
   TONG_TIEN            int,
   GHI_CHU              text,
   TRANG_THAI_KHOA      bool,
   NGAY_LAP_HT          timestamp default CURRENT_TIMESTAMP comment 'Ngay Lap tu chay theo he thong',
   DA_THANH_TOAN        bool comment 'Thuoc tinh kiem tra phie, bo qua neu phieu duoc tick la da thanh toan',
   primary key (PHIEUXUATID)
);

alter table CHI_TIET_PHIEU_XUAT add constraint FK_CAC_LOAI_HANG foreign key (PHIEUXUATID)
      references PHIEU_XUAT (PHIEUXUATID) on delete restrict on update restrict;

alter table CHI_TIET_PHIEU_XUAT add constraint FK_CO_HANG_HOA foreign key (HANGHOAID)
      references HANG_HOA (HANGHOAID) on delete restrict on update restrict;

alter table PHIEU_XUAT add constraint FK_THUOC_BAN foreign key (BANID)
      references BAN (BANID) on delete restrict on update restrict;

