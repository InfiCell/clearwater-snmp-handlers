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
 *        : mib2c.array-user.conf 15997 2007-03-25 22:28:35Z dts12 $
 *
 *  $Id:$
 */

#include "alarm_active_table.hpp"
#include "log.h"

#include <string>
using namespace std;

static netsnmp_handler_registration* my_handler = NULL;
static netsnmp_table_array_callbacks cb;

oid alarmModelTable_oid[] = { alarmModelTable_TABLE_OID };
size_t alarmModelTable_oid_len = OID_LENGTH(alarmModelTable_oid);

oid alarmActiveTable_oid[] = { alarmActiveTable_TABLE_OID };
size_t alarmActiveTable_oid_len = OID_LENGTH(alarmActiveTable_oid);

static oid zero_dot_zero_oid[] = { ZERO_DOT_ZERO_OID };
static oid alarm_active_state_oid[] = { ALARM_ACTIVE_STATE_OID };
static oid alarm_clear_state_oid[] = { ALARM_CLEAR_STATE_OID };

static oid entry_column_oid[] = { ENTRY_COLUMN_OID };

std::string local_ip;

/************************************************************
 *
 *  Initialize the alarmActiveTable table by defining its contents
 *  and how it's structured
 */
int init_alarmActiveTable(std::string ip)
{
  local_ip = ip;
  netsnmp_table_registration_info *table_info;

  if (my_handler)
  {
    TRC_ERROR("initialize_table_alarmActiveTable called again");
    return SNMP_ERR_NOERROR;
  }

  memset(&cb, 0x00, sizeof(cb));

  /** create the table structure itself */
  table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);

  my_handler = netsnmp_create_handler_registration("alarmActiveTable",
                                                   netsnmp_table_array_helper_handler,
                                                   alarmActiveTable_oid,
                                                   alarmActiveTable_oid_len,
                                                   HANDLER_CAN_RONLY);
            
  if (!my_handler || !table_info)
  {
    TRC_ERROR("malloc failed: initialize_table_alarmActiveTable");
    return SNMP_ERR_GENERR;
  }

  /*
   * Setting up the table's definition
   */

  /** index: alarmListName */
  netsnmp_table_helper_add_index(table_info, ASN_OCTET_STR);
  /** index: alarmActiveDateAndTime */
  netsnmp_table_helper_add_index(table_info, ASN_OCTET_STR);
  /** index: alarmActiveIndex */
  netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);

  table_info->min_column = alarmActiveTable_COL_MIN;
  table_info->max_column = alarmActiveTable_COL_MAX;

  /*
   * registering the table with the master agent
   */
  cb.get_value = alarmActiveTable_get_value;
  cb.container = netsnmp_container_find("alarmActiveTable_primary:"
                                        "alarmActiveTable:"
                                        "table_container");
  cb.can_set = 0;

  DEBUGMSGTL(("initialize_table_alarmActiveTable", "Registering as table array\n"));

  netsnmp_table_container_register(my_handler, table_info, &cb, cb.container, 1);

  return SNMP_ERR_NOERROR;
}

/************************************************************
 *
 *  This routine is called for get requests to copy the data
 *  from the context to the varbind for the request.
 */
int alarmActiveTable_get_value(netsnmp_request_info* request,
                              netsnmp_index* item,
                              netsnmp_table_request_info* table_info)
{
  netsnmp_variable_list* var = request->requestvb;
  alarmActiveTable_context* context = (alarmActiveTable_context*) item;

  switch(table_info->colnum)
  {
    case COLUMN_ALARMACTIVEENGINEID:
    {
      // Cannot obtain with SNMPv2 so use zero-length-string //
      static std::string empty_string  = "";
      snmp_set_var_typed_value(var, ASN_OCTET_STR,
                               (u_char*) &empty_string,
                               sizeof(empty_string));
    }
    break;

    case COLUMN_ALARMACTIVEENGINEADDRESSTYPE:
    {
     snmp_set_var_typed_value(var, ASN_OCTET_STR,
                               (u_char*) &local_ip,
                               sizeof(local_ip));
    }
    break;

    case COLUMN_ALARMACTIVEENGINEADDRESS:
    {
      // This is of type InetAddressType and will either be
      // IPv4 or IPv6
      static std::string ip_type;
      ip_type = (local_ip.length()==4) ? "ipV4" : "ipV6";
      snmp_set_var_typed_value(var, ASN_OCTET_STR,
                               (u_char*) &ip_type,
                               sizeof(ip_type));
    }
    break;

    case COLUMN_ALARMACTIVECONTEXTNAME:
    {
      // We do not support multiple contexts so this object
      // will be set to the empty string
      static std::string empty_string  = "";
      snmp_set_var_typed_value(var, ASN_OCTET_STR,
                               (u_char*) &empty_string,
                               empty_string.length());
    }
    break;
    
    case COLUMN_ALARMACTIVEVARIABLES:
    {
      // The number of variables in alarmActiveVariableTable for
      // this alarm. See as we have no such table this will be 0.
      static unsigned long variables = 0;
      snmp_set_var_typed_value(var, ASN_UNSIGNED,
                               (u_char*) &variables,
                               sizeof(variables));
    }
    break;

    case COLUMN_ALARMACTIVENOTIFICATIONID:
    {
      if (context->_alarm_table_def->severity() == AlarmDef::CLEARED)
      {
        snmp_set_var_typed_value(var, ASN_OBJECT_ID,
                                 (u_char*) alarm_clear_state_oid,
                                 sizeof(alarm_clear_state_oid));
      }
      else
      {
        snmp_set_var_typed_value(var, ASN_OBJECT_ID,
                                 (u_char*) alarm_active_state_oid,
                                 sizeof(alarm_active_state_oid));
      }
    }
    break;
    
    case COLUMN_ALARMACTIVERESOURCEID:
    {
      // None of our alarms have resources so this will always
      // be the 0.0 OID
      
      snmp_set_var_typed_value(var, ASN_OBJECT_ID,
                               (u_char*) zero_dot_zero_oid,
                               sizeof(zero_dot_zero_oid));
    }
    break;
    
    case COLUMN_ALARMACTIVEDESCRIPTION:
    {
      snmp_set_var_typed_value(var, ASN_OCTET_STR,
                               (u_char*) context->_alarm_table_def->description().c_str(),
                               context->_alarm_table_def->description().length());
    }
    break;

    case COLUMN_ALARMACTIVELOGPOINTER:
    {
      // We don't keep log entries so this will always be
      // the 0.0 OID
      snmp_set_var_typed_value(var, ASN_OBJECT_ID,
                               (u_char*) zero_dot_zero_oid,
                               sizeof(zero_dot_zero_oid));
    }
    break;

    case COLUMN_ALARMACTIVEMODELPOINTER:
    {
      // Convert the index string OID
      oid index_oid = context->_index.oids;

      // Append the index array on to the Alarm Model Table OID, inserting
      // the OID ".1.3." for the entry in the first non index column
      model_pointer = new oid[sizeof(alarmModelTable_oid) + sizeof(entry_column_oid) + sizeof(index_oid)];
      copy(alarmModelTable_oid, alarmModelTable_oid + sizeof(alarmModelTable_oid), model_pointer);
      copy(entry_column_oid, entry_column_oid + sizeof(entry_column_oid), model_pointer + sizeof(alarmModelTable_oid));
      copy(index_oid, index_oid + sizeof(index_oid), model_pointer + sizeof(alarmModelTable_oid) + sizeof(entry_column_oid);

      snmp_set_var_types_value(var, ASN_OBJECT_ID,
                               (u_char*) model_pointer,
                               sizeof(model_pointer));

    }
    break;
    
    case COLUMN_ALARMMODELSPECIFICPOINTER:
    {
      // This would point to the model-specific active alarm list
      // for this alarm. We do not support model-specific Alarm-MIB
      // and hence this will always be the 0.0 OID
      snmp_set_var_types_value(var, ASN_OBJECT_ID,
                               (u_char*) zero_dot_zero_oid,
                               sizeof(zero_dot_zero_oid));
    }
    break;
    
    
    default: /** We shouldn't get here */
    {
      TRC_ERROR("unknown column: alarmActiveTable_get_value");
      return SNMP_ERR_GENERR;
    }
  }

  return SNMP_ERR_NOERROR;
}

/************************************************************
 * 
 *  Create a new row context and initialize its oid index.
 */
void alarmActiveTable_create_row(char* name,
                                 alarmActiveTable_SNMPDateTime* datetime,
                                 unsigned long index)
{
  int current_state;
  alarmActiveTable_context* ctx = SNMP_MALLOC_TYPEDEF(alarmActiveTable_context);
  if (!ctx)
  {
    TRC_ERROR("malloc failed: alarmActiveTable_create_row");
    return;
  }
        
  if (alarmActiveTable_index_to_oid(name, datetime, index, &ctx->_index) != SNMP_ERR_NOERROR)
  {
    if (ctx->_index.oids != NULL)
    {
      free(ctx->_index.oids);
    }

    free(ctx);
    return;
  }
  // If an instance of an alarm is raised that already exists within the Active
  // Alarm Table but with different severity we should remove the old alarm.
  current_state = ctx->alarm_table_def.state();
  if current_state != 1;
  {
    for (int i=2; i<=6; i++)
    {
      (ctx->_index).back() = i;
      if (CONTAINER_FIND(cb.container, ctx) != NULL && current_state != i)
      {
        CONTAINER_REMOVE(cb.container,ctx);
      }
    }
  }
  (ctw->_index).back() = current_state;
  if (ctx)
  {
    CONTAINER_INSERT(cb.container, ctx);
  }
}

/************************************************************
 *
 * Delete a row
 */
void alarmActiveTable_delete_row(unsigned long index)
{
  alarmActiveTable_context* ctx = SNMP_MALLOC_TYPEDEF(alarmActiveTable_context);
  if (!ctx)
  {
    TRC_ERROR("malloc failed: alarmActiveTable_remove_row");
    return;
  }
  
  if (ctx)
  {
    CONTAINER_REMOVE(cb.container, ctx)
  }
}
/************************************************************
 *
 *  Convert table index components to an oid.
 */
int alarmActiveTable_index_to_oid(char* name,
                                 alarmActiveTable_SNMPDateTime* datetime,
                                 unsigned long index,
                                 netsnmp_index *oid_idx)
{
  int err = SNMP_ERR_NOERROR;

  netsnmp_variable_list var_alarmListName;
  netsnmp_variable_list var_alarmActiveDateAndTime;
  netsnmp_variable_list var_alarmActiveIndex;

  /*
   * set up varbinds
   */
  memset(&var_alarmListName, 0x00, sizeof(var_alarmListName));
  var_alarmListName.type = ASN_OCTET_STR;
  memset(&var_alarmActiveDateAndTime, 0x00, sizeof(var_alarmActiveDateAndTime));
  var_alarmActiveDateAndTime.type = ASN_OCTET_STR;
  memset(&var_alarmActiveIndex, 0x00, sizeof(var_alarmActiveIndex));
  var_alarmActiveIndex.type = ASN_UNSIGNED;

  /*
   * chain index varbinds together
   */
  var_alarmListName.next_variable = &var_alarmActiveDateAndTime;
  var_alarmActiveDateAndTime.next_variable = &var_alarmActiveIndex;
  var_alarmActiveIndex.next_variable =  NULL;


  DEBUGMSGTL(("verbose:alarmActiveTable:alarmActiveTable_index_to_oid", "called\n"));

  snmp_set_var_value(&var_alarmListName, (u_char*) name, strlen(name));
  snmp_set_var_value(&var_alarmActiveDateAndTime, (u_char*) &datetime, sizeof(datetime));
  snmp_set_var_value(&var_alarmActiveIndex, (u_char*) &index, sizeof(index));

  err = build_oid(&oid_idx->oids, &oid_idx->len, NULL, 0, &var_alarmListName);
  if (err)
  {
    TRC_ERROR("error %d converting index to oid: alarmActiveTable_index_to_oid", err);
  }

  /*
   * parsing may have allocated memory. free it.
   */
  snmp_reset_var_buffers(&var_alarmListName);

  return err;
} 
