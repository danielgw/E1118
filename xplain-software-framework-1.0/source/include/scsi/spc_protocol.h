/**
 * \file
 *
 * \brief SCSI Primary Commands
 *
 * This file contains definitions of some of the commands found in the
 * SPC-2 standard.
 *
 * Copyright (C) 2009 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#ifndef SCSI_SPC_PROTOCOL_H_INCLUDED
#define SCSI_SPC_PROTOCOL_H_INCLUDED

#define SCSI_CMD_TEST_UNIT_READY		0x00
#define SCSI_CMD_REQUEST_SENSE			0x03
#define SCSI_CMD_INQUIRY			0x12
#define SCSI_CMD_MODE_SELECT6			0x15
#define SCSI_CMD_MODE_SENSE6			0x1a
#define SCSI_CMD_SEND_DIAGNOSTIC		0x1d
#define SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL	0x1e
#define SCSI_CMD_MODE_SENSE10			0x5a
#define SCSI_CMD_REPORT_LUNS			0xa0

/* May be set in byte 0 of the INQUIRY CDB */
#define SCSI_INQ_REQ_EVPD	0x01	//!< Enable Vital Product Data

COMPILER_PACK_SET(1);

/**
 * \brief SCSI Standard Inquiry data structure
 */
struct scsi_inquiry_data {
	uint8_t	pq_pdt;			//!< Periph Qual / Periph Dev Type
#define SCSI_INQ_PQ_CONNECTED	0x00	//!< Peripheral connected
#define SCSI_INQ_PQ_NOT_CONN	0x20	//!< Peripheral not connected
#define SCSI_INQ_PQ_NOT_SUPP	0x60	//!< Peripheral not supported
#define SCSI_INQ_DT_DIR_ACCESS	0x00	//!< Direct Access (SBC)
#define SCSI_INQ_DT_SEQ_ACCESS	0x01	//!< Sequential Access
#define SCSI_INQ_DT_PRINTER	0x02	//!< Printer
#define SCSI_INQ_DT_PROCESSOR	0x03	//!< Processor device
#define SCSI_INQ_DT_WRITE_ONCE	0x04	//!< Write-once device
#define SCSI_INQ_DT_CD_DVD	0x05	//!< CD/DVD device
#define SCSI_INQ_DT_OPTICAL	0x07	//!< Optical Memory
#define SCSI_INQ_DT_MC		0x08	//!< Medium Changer
#define SCSI_INQ_DT_ARRAY	0x0c	//!< Storage Array Controller
#define SCSI_INQ_DT_ENCLOSURE	0x0d	//!< Enclosure Services
#define SCSI_INQ_DT_RBC		0x0e	//!< Simplified Direct Access
#define SCSI_INQ_DT_OCRW	0x0f	//!< Optical card reader/writer
#define SCSI_INQ_DT_BCC		0x10	//!< Bridge Controller Commands
#define SCSI_INQ_DT_OSD		0x11	//!< Object-based Storage
#define SCSI_INQ_DT_NONE	0x1f	//!< No Peripheral
	uint8_t	flags1;			//!< Flags (byte 1)
#define SCSI_INQ_RMB		0x80	//!< Removable Medium
	uint8_t	version;		//!< Version
#define SCSI_INQ_VER_NONE	0x00	//!< No standards conformance
#define SCSI_INQ_VER_SPC	0x03	//!< SCSI Primary Commands
#define SCSI_INQ_VER_SPC2	0x04	//!< SCSI Primary Commands - 2
#define SCSI_INQ_VER_SPC3	0x05	//!< SCSI Primary Commands - 3
#define SCSI_INQ_VER_SPC4	0x06	//!< SCSI Primary Commands - 4
	uint8_t	flags3;			//!< Flags (byte 3)
#define SCSI_INQ_NORMACA	0x20	//!< Normal ACA Supported
#define SCSI_INQ_HISUP		0x10	//!< Hierarchial LUN addressing
#define SCSI_INQ_RSP_SPC2	0x02	//!< SPC-2 / SPC-3 response format
	uint8_t addl_len;		//!< Additional Length (n-4)
#define SCSI_INQ_ADDL_LEN(tot)	((tot) - 5) //!< Total length is \a tot
	uint8_t	flags5;			//!< Flags (byte 5)
#define SCSI_INQ_SCCS		0x80
	uint8_t	flags6;			//!< Flags (byte 6)
#define SCSI_INQ_BQUE		0x80
#define SCSI_INQ_ENCSERV	0x40
#define SCSI_INQ_MULTIP		0x10
#define SCSI_INQ_MCHGR		0x08
#define SCSI_INQ_ADDR16		0x01
	uint8_t flags7;			//!< Flags (byte 7)
#define SCSI_INQ_WBUS16		0x20
#define SCSI_INQ_SYNC		0x10
#define SCSI_INQ_LINKED		0x08
#define SCSI_INQ_CMDQUE		0x02
	uint8_t	vendor_id[8];		//!< T10 Vendor Identification
	uint8_t	product_id[16];		//!< Product Identification
	uint8_t	product_rev[4];		//!< Product Revision Level
};

COMPILER_PACK_RESET();

/* Vital Product Data page codes */
enum scsi_vpd_page_code {
	SCSI_VPD_SUPPORTED_PAGES	= 0x00,
	SCSI_VPD_UNIT_SERIAL_NUMBER	= 0x80,
	SCSI_VPD_DEVICE_IDENTIFICATION	= 0x83,
};
#define SCSI_VPD_HEADER_SIZE	4

/* Constants associated with the Device Identification VPD page */
#define SCSI_VPD_ID_HEADER_SIZE		4

#define SCSI_VPD_CODE_SET_BINARY	1
#define SCSI_VPD_CODE_SET_ASCII		2
#define SCSI_VPD_CODE_SET_UTF8		3

#define SCSI_VPD_ID_TYPE_T10		1

/* REQUEST SENSE response flags: 1st byte */
#define SCSI_SENSE_VALID		0x80
#define SCSI_SENSE_CURRENT		0x70
#define SCSI_SENSE_DEFERRED		0x71

/* 3rd byte */
#define SCSI_SENSE_FILEMARK		0x80
#define SCSI_SENSE_EOM			0x40
#define SCSI_SENSE_ILI			0x20
#define SCSI_SENSE_KEY(x)		(x)

/* 8th byte */
#define SCSI_SENSE_ADDL_LEN(total_len)	((total_len) - 8)

/* 16th byte */
#define SCSI_SENSE_SKSV			0x80

/* Sense keys */
enum scsi_sense_key {
	SCSI_SK_NO_SENSE	= 0x0,
	SCSI_SK_RECOVERED_ERROR	= 0x1,
	SCSI_SK_NOT_READY	= 0x2,
	SCSI_SK_MEDIUM_ERROR	= 0x3,
	SCSI_SK_HARDWARE_ERROR	= 0x4,
	SCSI_SK_ILLEGAL_REQUEST	= 0x5,
	SCSI_SK_UNIT_ATTENTION	= 0x6,
	SCSI_SK_DATA_PROTECT	= 0x7,
	SCSI_SK_BLANK_CHECK	= 0x8,
	SCSI_SK_VENDOR_SPECIFIC	= 0x9,
	SCSI_SK_COPY_ABORTED	= 0xa,
	SCSI_SK_ABORTED_COMMAND	= 0xb,
	SCSI_SK_VOLUME_OVERFLOW	= 0xd,
	SCSI_SK_MISCOMPARE	= 0xe,
};

/* Additional Sense Code / Additional Sense Code Qualifier pairs */
enum scsi_asc_ascq {
	SCSI_ASC_NO_ADDITIONAL_SENSE_INFO		= 0x0000,
	SCSI_ASC_LU_NOT_READY_REBUILD_IN_PROGRESS	= 0x0405,
	SCSI_ASC_WRITE_ERROR				= 0x0c00,
	SCSI_ASC_UNRECOVERED_READ_ERROR			= 0x1100,
	SCSI_ASC_INVALID_COMMAND_OPERATION_CODE		= 0x2000,
	SCSI_ASC_INVALID_FIELD_IN_CDB			= 0x2400,
	SCSI_ASC_MEDIUM_NOT_PRESENT			= 0x3a00,
	SCSI_ASC_INTERNAL_TARGET_FAILURE		= 0x4400,
};

/* Mode page stuff */

enum scsi_spc_mode_page_code {
	SCSI_MS_PAGE_VENDOR_SPEC			= 0x00,
	SCSI_MS_PAGE_ALL				= 0x3f,
};

enum scsi_spc_mode_sense_pc {
	SCSI_MS_PC_CURRENT		= 0,
	SCSI_MS_PC_CHANGEABLE		= 1,
	SCSI_MS_PC_DEFAULT		= 2,
	SCSI_MS_PC_SAVED		= 3,
};

static inline bool scsi_mode_sense_dbd_is_set(const uint8_t *cdb)
{
	return (cdb[1] >> 3) & 1;
}

static inline uint8_t scsi_mode_sense_get_page_code(const uint8_t *cdb)
{
	return cdb[2] & 0x3f;
}

static inline uint8_t scsi_mode_sense_get_pc(const uint8_t *cdb)
{
	return cdb[2] >> 6;
}

/**
 * \brief SCSI Mode Parameter Header used by MODE SELECT(6) and MODE
 * SENSE(6)
 */
struct scsi_mode_param_header6 {
	uint8_t	mode_data_length;		//!< Number of bytes after this
	uint8_t	medium_type;			//!< Medium Type
	uint8_t	device_specific_parameter;	//!< Defined by command set
	uint8_t block_descriptor_length;	//!< Length of block descriptors
};

/**
 * \brief SCSI Mode Parameter Header used by MODE SELECT(10) and MODE
 * SENSE(10)
 */
struct scsi_mode_param_header10 {
	be16_t	mode_data_length;		//!< Number of bytes after this
	uint8_t	medium_type;			//!< Medium Type
	uint8_t	device_specific_parameter;	//!< Defined by command set
	uint8_t	flags4;				//!< LONGLBA in bit 0
	uint8_t	reserved;
	be16_t	block_descriptor_length;	//!< Length of block descriptors
};

/**
 * \brief SCSI Page_0 Mode Page header (SPF not set)
 */
struct scsi_mode_page_0_header {
	uint8_t	page_code;
#define SCSI_PAGE_CODE_PS	(1 << 7)	//!< Parameters Saveable
#define SCSI_PAGE_CODE_SPF	(1 << 6)	//!< SubPage Format
	uint8_t	page_length;			//!< Number of bytes after this
#define SCSI_MS_PAGE_LEN(total)	((total) - 2)
};

#endif /* SCSI_SPC_PROTOCOL_H_INCLUDED */
