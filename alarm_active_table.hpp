/**
* Project Clearwater - IMS in the Cloud
* Copyright (C) 2014 Metaswitch Networks Ltd
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation, either version 3 of the License, or (at your
* option) any later version, along with the "Special Exception" for use of
* the program along with SSL, set forth below. This program is distributed
* in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR
* A PARTICULAR PURPOSE. See the GNU General Public License for more
* details. You should have received a copy of the GNU General Public
* License along with this program. If not, see
* <http://www.gnu.org/licenses/>.
*
* The author can be reached by email at clearwater@metaswitch.com or by
* post at Metaswitch Networks Ltd, 100 Church St, Enfield EN2 6BQ, UK
*
* Special Exception
* Metaswitch Networks Ltd grants you permission to copy, modify,
* propagate, and distribute a work formed by combining OpenSSL with The
* Software, or a work derivative of such a combination, even if such
* copying, modification, propagation, or distribution would otherwise
* violate the terms of the GPL. You must comply with the GPL in all
* respects for all of the code used other than OpenSSL.
* "OpenSSL" means OpenSSL toolkit software distributed by the OpenSSL
* Project and licensed under the OpenSSL Licenses, or a work based on such
* software and licensed under the OpenSSL Licenses.
* "OpenSSL Licenses" means the OpenSSL License and Original SSLeay License
* under which the OpenSSL Project distributes the OpenSSL toolkit software,
* as those licenses appear in the file LICENSE-OPENSSL.
*/

/*
 *  Note: this file originally auto-generated by mib2c using
 *         : mib2c.array-user.conf 15997 2007-03-25 22:28:35Z dts12 $
 *
 *  $Id:$
 */

#ifndef ALARM_ACTIVE_TABLE_HPP
#define ALARM_ACTIVE_TABLE_HPP

#include <alarm_table_defs.hpp>
#include "alarm_trap_sender.hpp"
#ifdef __cplusplus
extern "C" {
#endif

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include <net-snmp/library/snmp_assert.h>
    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include <string>
using namespace std;

typedef struct alarmActiveTable_context_s {
    netsnmp_index _index; /** THIS MUST BE FIRST!!! */

    std::string _date_time;

    AlarmTableDef* _alarm_table_def;

} alarmActiveTable_context;

/*************************************************************
 *
 *  function declarations
 */
int init_alarmActiveTable(std::string);
int alarmActiveTable_get_value(netsnmp_request_info*, netsnmp_index*, netsnmp_table_request_info*);

alarmActiveTable_context* alarmActiveTable_create_row(char*, alarmActiveTable_SNMPDateTime*, unsigned long);
void alarmActiveTable_delete_row(unsigned long);
int alarmActiveTable_index_to_oid(char*, std::string, unsigned long, netsnmp_index*);

/*************************************************************
 *
 *  oid declarations
 */
extern oid alarmActiveTable_oid[];
extern size_t alarmActiveTable_oid_len;

#define alarmModelTable_TABLE_OID 1,3,6,1,2,1,118,1,1,2
#define alarmActiveTable_TABLE_OID 1,3,6,1,2,1,118,1,2,2
    
#define ZERO_DOT_ZERO_OID 0,0
#define ALARM_ACTIVE_STATE_OID 1,3,6,1,2,1,118,0,2
#define ALARM_CLEAR_STATE_OID 1,3,6,1,2,1,118,0,3

#define ENTRY_COLUMN_OID 1,3

/*************************************************************
 *
 *  column number definitions for table alarmModelTable
 */
#define COLUMN_ALARMLISTNAME 1
#define COLUMN_ALARMACTIVEDATEANDTIME 2
#define COLUMN_ALARMACTIVEINDEX 3
#define COLUMN_ALARMACTIVEENGINEID 4
#define COLUMN_ALARMACTIVEENGINEADDRESSTYPE 5
#define COLUMN_ALARMACTIVEENGINEADDRESS 6
#define COLUMN_ALARMACTIVECONTEXTNAME 7
#define COLUMN_ALARMACTIVEVARIABLES 8
#define COLUMN_ALARMACTIVENOTIFICATIONID 9
#define COLUMN_ALARMACTIVERESOURCEID 10
#define COLUMN_ALARMACTIVEDESCRIPTION 11
#define COLUMN_ALARMACTIVELOGPOINTER 12
#define COLUMN_ALARMACTIVEMODELPOINTER 13
#define COLUMN_ALARMACTIVESPECIFICPOINTER 14
#define alarmActiveTable_COL_MIN 4
#define alarmActiveTable_COL_MAX 14

#define ROWSTATUS_ACTIVE 1

#define ITUALARMTABLEROW_INDEX 13
#define ITUALARMTABLEROW_SEVERITY 14

#ifdef __cplusplus
}
#endif

#endif /** ALARMMODELTABLE_HPP */
