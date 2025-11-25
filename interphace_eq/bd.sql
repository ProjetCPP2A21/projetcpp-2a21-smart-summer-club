--------------------------------------------------------
--  Fichier créé - vendredi-novembre-14-2025   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table EQUIPEMENT
--------------------------------------------------------

  CREATE TABLE "HOUSSEM"."EQUIPEMENT" 
   (	"ID" VARCHAR2(20 BYTE), 
	"NOM" VARCHAR2(20 BYTE), 
	"PRIX" VARCHAR2(20 BYTE), 
	"TYPE" VARCHAR2(20 BYTE), 
	"ETAT" VARCHAR2(20 BYTE), 
	"QUANTITE" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
REM INSERTING into HOUSSEM.EQUIPEMENT
SET DEFINE OFF;
Insert into HOUSSEM.EQUIPEMENT (ID,NOM,PRIX,TYPE,ETAT,QUANTITE) values ('xsx','xx','4','x','disponible','410');
Insert into HOUSSEM.EQUIPEMENT (ID,NOM,PRIX,TYPE,ETAT,QUANTITE) values ('41','000252','5','41000','en maintenance','44');
Insert into HOUSSEM.EQUIPEMENT (ID,NOM,PRIX,TYPE,ETAT,QUANTITE) values ('sdq','000252','5','41000','en maintenance','44');
