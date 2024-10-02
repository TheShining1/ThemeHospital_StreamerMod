#pragma once

struct HospObj_UnkStruct_0xC {
  int32_t field0_0x0;
  int8_t field1_0x4;
  int8_t field2_0x5;
  int8_t field3_0x6;
  int8_t field4_0x7;
  int8_t field5_0x8;
  int8_t field6_0x9;
  int8_t field7_0xa;
  int8_t field8_0xb;
};

struct GameObject {
  int8_t Unk_0;
  int8_t Unk_1;
  int8_t Unk_2;
  int8_t Unk_3;
  int8_t Unk_4;
  int8_t Unk_5;
  int8_t Unk_6;
  int8_t Unk_7;
  int16_t FrameIndex;
  int16_t Unk_a;                         /* zero */
  int8_t Type;
  int8_t AnimationType;
  int8_t Unk_e;
  int8_t DAT_004c484e;
  int8_t Unk_10;
  int8_t Unk_11;
  int8_t DAT_004c484c;
  int8_t field_0x13;                   // == field_0x5;
  int8_t field_0x14;                   // == field_0x7;
  int8_t Unk_15;
  int16_t HospIndex;
  int8_t Unk_18;
  int16_t Unk_19;
  int16_t Unk_1b;
  int8_t Unk_1d;
  int8_t Unk_1e;
  int8_t Unk_1f;
  int8_t Unk_20;
  int8_t Unk_21;
  int8_t Unk_22;
  int8_t Unk_23;
  int8_t Unk_24;
  int8_t Unk_25;
  int8_t Unk_26;
  int8_t Unk_27;
  int8_t Unk_28;
  int8_t Unk_29;
  struct HospObj_UnkStruct_0xC UnkStruct_2a;
  int8_t Unk_36;
  int TimesUsed;
  int16_t Unk_3b;
  int16_t Unk_3d;
  int16_t Unk_3f;
  int16_t Unk_41;
  int16_t Unk_43;
  int16_t Unk_45;
  int16_t Unk_47;
  int16_t HospObjIndex;
  int16_t Unk_4b;
  int16_t Unk_4d;
  int16_t Unk_4f;
  int16_t Unk_51;
  int16_t Unk_53;
  int16_t Unk_55;
  int8_t Unk_57;
  int8_t Unk_58;
  int16_t Unk_59;
  int16_t Unk_5b;
  int8_t Unk_5d;
  int8_t Unk_5e;
  int8_t Unk_5f;
  int8_t Unk_60;
  int8_t Unk_61;
  int8_t Unk_62;
  int8_t Unk_63;
  int16_t Unk_64;
  int16_t Unk_66;
  int16_t Unk_68;
  int8_t Unk_6a;
  int8_t Unk_6b;
  int32_t Unk_6c;
  int32_t Unk_70;
  int32_t Status;
  int16_t Unk_78;
  int16_t Unk_7a;
  int16_t Patience;
  int16_t Unk_7e;
  int16_t Unk_80;
  int16_t Unk_82;             /* clock? */
  int8_t NameIndex;
  int8_t SurnameIndex;
  int16_t Drink;              /* 0 - 100 union? */
  int16_t Bowel;              /* union? */
  int16_t VomitLevel;         /* union? */
  int16_t Unk_8c;
  int16_t Unk_8e;             /* union? */
  int8_t Unk_90;
  int8_t Unk_91;
  int16_t DiagnosisProgress;  /* 1000 - diagnosed */
  int32_t Unk_94;             /* clock? */
  int16_t Unk_98;             /* union? */
  int16_t Unk_9a;
  int16_t Unk_9c;
  int8_t Unk_9e;
  int8_t Unk_9f;
  int8_t Unk_a0;
  int8_t Unk_a1;
  int8_t Unk_a2;
  int8_t Unk_a3;
  int8_t Unk_a4;
  int8_t Unk_a5;
  int8_t Unk_a6;
  int8_t Unk_a7;
  int8_t Disease;
  int8_t DiseaseDiagnosed;
  int8_t Unk_aa;
  int8_t UnkIndex_ab;
  int8_t Unk_ac;
  int8_t Unk_ad;
  uint8_t Contagious;
};