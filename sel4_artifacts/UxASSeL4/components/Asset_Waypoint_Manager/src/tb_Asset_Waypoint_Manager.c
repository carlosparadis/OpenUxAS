/**************************************************************************
  Copyright (c) 2013-2016 Rockwell Collins and the University of
  Minnesota. Developed with the sponsorship of the Defense Advanced
  Research Projects Agency (DARPA).

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this data, including any software or models
  in source or binary form, as well as any drawings,
  specifications, and documentation (collectively "the Data"), to
  deal in the Data without restriction, including without
  limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Data, and to
  permit persons to whom the Data is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Data.

  THE DATA IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS, SPONSORS,
  DEVELOPERS, CONTRIBUTORS, OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE DATA OR THE USE OR OTHER DEALINGS IN THE
  DATA.
 **************************************************************************/

/**************************************************************************

  ***AUTOGENERATED CODE: DO NOT MODIFY***

This C file contains the implementations of the AADL primitives
used by user-level declarations for thread Asset_Waypoint_Manager.

The user code runs in terms of "dispatchers", which cause
dispatch user-level handlers to execute.  These handlers can
communicate using the standard AADL primitives, which are mapped
to C functions.

The send/receive handlers are not thread safe in CAmkES; it is
assumed that this is handled by the CAmkES sequentialized access
to the dispatch handler.  There is only one dispatch interface
for the component containing all of the dispatch points.

They are thread safe for eChronos.

The read/write handlers are thread safe because the writer comes
through a dispatch interface but the reader is "local" on a dispatch
interface and so contention may occur.

 **************************************************************************/

#include "tb_Asset_Waypoint_Manager.h"
#include <string.h>
#include <camkes.h>

/************************************************************************
 * periodic_dispatcher Declarations
 *
 ************************************************************************/

static bool tb_occurred_periodic_dispatcher;
static int64_t tb_time_periodic_dispatcher;

/************************************************************************
 * periodic_dispatcher_write_int64_t
 * Invoked from remote periodic dispatch thread.
 *
 * This function records the current time and triggers the active thread
 * dispatch from a periodic event.  Note that the periodic dispatch
 * thread is the *only* thread that triggers a dispatch, so we do not
 * mutex lock the function.
 *
 ************************************************************************/

bool periodic_dispatcher_write_int64_t(const int64_t * arg) {
    tb_occurred_periodic_dispatcher = true;
    tb_time_periodic_dispatcher = *arg;
    MUTEXOP(tb_dispatch_sem_post())
    return true;
}
void tb_timer_complete_callback(void *_ UNUSED) {
   // we want time in microseconds, not nanoseconds, so we divide by 1000.
   int64_t tb_time_periodic_dispatcher = tb_timer_time() / 1000LL;
   (void)periodic_dispatcher_write_int64_t(&tb_time_periodic_dispatcher);
   CALLBACKOP(tb_timer_complete_reg_callback(tb_timer_complete_callback, NULL));
}

static void tb_in_uart_packet_notification_handler(void * unused) {
  MUTEXOP(tb_dispatch_sem_post())
  CALLBACKOP(tb_in_uart_packet_notification_reg_callback(tb_in_uart_packet_notification_handler, NULL));
}
/************************************************************************
 *  tb_Asset_Waypoint_Manager_write_waypoint_write:
 * Invoked from user code in the local thread.
 *
 * This is the function invoked by the local thread to make a
 * call to write to a remote data port.
 *
 ************************************************************************/

bool tb_Asset_Waypoint_Manager_write_waypoint_write(void) {
    bool tb_result = true ; 

    asset_waypoint_manager_waypoint_write____waypoint_manager_waypoint_write_emit();
    asset_waypoint_manager_waypoint_write____virtual_machine_waypoint_write_emit();
    return tb_result;
}/************************************************************************
 *
 * Static variables and queue management functions for event port:
 *     waypoint_read_vm
 *
 ************************************************************************/

static bool waypoint_read_vm_index = false;

/************************************************************************
 *  waypoint_read_vm_callback:
 * Invoked by: remote RPC
 *
 * This is the function invoked by a remote RPC to write to an active-thread
 * input event port.  It increments a count of received messages.
 *
 ************************************************************************/

bool waypoint_read_vm_callback(void *_ UNUSED) {
    waypoint_read_vm_index = true;
    CALLBACKOP(waypoint_read_vm_reg_callback(waypoint_read_vm_callback, NULL));
    return true;
}

/************************************************************************
 *  tb_Asset_Waypoint_Manager_read_waypoint_read_vm:
 * Invoked from local active thread.
 *
 * This is the function invoked by the active thread to decrement the
 * input event index.
 *
 ************************************************************************/

bool tb_Asset_Waypoint_Manager_read_waypoint_read_vm() {
    bool result;
    result = waypoint_read_vm_index;
    waypoint_read_vm_index = false;
    return result;
}
/************************************************************************
 *
 * Static variables and queue management functions for event port:
 *     waypoint_read_wm
 *
 ************************************************************************/

static bool waypoint_read_wm_index = false;

/************************************************************************
 *  waypoint_read_wm_callback:
 * Invoked by: remote RPC
 *
 * This is the function invoked by a remote RPC to write to an active-thread
 * input event port.  It increments a count of received messages.
 *
 ************************************************************************/

bool waypoint_read_wm_callback(void *_ UNUSED) {
    waypoint_read_wm_index = true;
    CALLBACKOP(waypoint_read_wm_reg_callback(waypoint_read_wm_callback, NULL));
    return true;
}

/************************************************************************
 *  tb_Asset_Waypoint_Manager_read_waypoint_read_wm:
 * Invoked from local active thread.
 *
 * This is the function invoked by the active thread to decrement the
 * input event index.
 *
 ************************************************************************/

bool tb_Asset_Waypoint_Manager_read_waypoint_read_wm() {
    bool result;
    result = waypoint_read_wm_index;
    waypoint_read_wm_index = false;
    return result;
}



void pre_init(void) {

    // Pre-initialization statements for periodic_dispatcher
    // Pre-initialization statements for Asset_Waypoint_Manager_initializer
    // Pre-initialization statements for tb_in_uart_packet
    CALLBACKOP(tb_in_uart_packet_notification_reg_callback(tb_in_uart_packet_notification_handler, NULL));
    // Pre-initialization statements for waypoint_read_vm
    // Pre-initialization statements for waypoint_read_wm

}

/************************************************************************
 *  tb_entrypoint_Asset_Waypoint_Manager_periodic_dispatcher:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void tb_entrypoint_Asset_Waypoint_Manager_periodic_dispatcher(const int64_t * in_arg) {
    component_entry((int64_t *) in_arg);

}

/************************************************************************
 *  tb_entrypoint_Asset_Waypoint_Manager_Asset_Waypoint_Manager_initializer:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void tb_entrypoint_Asset_Waypoint_Manager_Asset_Waypoint_Manager_initializer(const int64_t * in_arg) {
    component_init((int64_t *) in_arg);

}

/************************************************************************
 *  tb_entrypoint_tb_Asset_Waypoint_Manager_in_uart_packet:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void tb_entrypoint_tb_Asset_Waypoint_Manager_in_uart_packet(const SMACCM_DATA__UART_Packet_i * in_arg) {
    in_uart_packet((SMACCM_DATA__UART_Packet_i *) in_arg);

}

/************************************************************************
 *  tb_entrypoint_Asset_Waypoint_Manager_waypoint_read_vm:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void tb_entrypoint_Asset_Waypoint_Manager_waypoint_read_vm(void) {
}

/************************************************************************
 *  tb_entrypoint_Asset_Waypoint_Manager_waypoint_read_wm:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void tb_entrypoint_Asset_Waypoint_Manager_waypoint_read_wm(void) {
}


/************************************************************************
 * int run(void)
 * Main active thread function.
 *
 ************************************************************************/

int run(void) {

    // Port initialization routines

    // tb_timer_periodic(0, ((uint64_t)100)*NS_IN_MS);
    CALLBACKOP(tb_timer_complete_reg_callback(tb_timer_complete_callback, NULL));
    SMACCM_DATA__UART_Packet_i tb_in_uart_packet;


    {
    int64_t tb_dummy;
    tb_entrypoint_Asset_Waypoint_Manager_Asset_Waypoint_Manager_initializer(&tb_dummy);
    }
    // Initial lock to await dispatch input.
    MUTEXOP(tb_dispatch_sem_wait())
    for(;;) {
        MUTEXOP(tb_dispatch_sem_wait())

        // Drain the queues
        if (tb_occurred_periodic_dispatcher) {
            tb_occurred_periodic_dispatcher = false;
            tb_entrypoint_Asset_Waypoint_Manager_periodic_dispatcher(&tb_time_periodic_dispatcher);
        }
        while (tb_in_uart_packet_dequeue((SMACCM_DATA__UART_Packet_i*)&tb_in_uart_packet)) {
            tb_entrypoint_tb_Asset_Waypoint_Manager_in_uart_packet(&tb_in_uart_packet);
        }

    }

    // Won't ever get here, but form must be followed
    return 0;
}

