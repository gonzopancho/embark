/*
 * nullelement.{cc,hh} -- do-nothing element
 * Eddie Kohler
 *
 * Copyright (c) 1999-2000 Massachusetts Institute of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, subject to the conditions
 * listed in the Click LICENSE file. These conditions include: you must
 * preserve this copyright notice, and you cannot mention the copyright
 * holders in advertising related to the Software without their permission.
 * The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
 * notice is a summary of the Click LICENSE file; the license in that file is
 * legally binding.
 */

#include <click/config.h>
#include "nullelement.hh"
#include <iostream>
#include <click/task.hh>
#include <click/routerthread.hh>
#include <click/router.hh>
#include <click/master.hh>
#include <click/glue.hh>
#include <click/args.hh>
#include <click/task.hh>
#include <click/error.hh>


CLICK_DECLS

NullElement::NullElement()
{
}

NullElement::~NullElement()
{
}

  Packet *
NullElement::simple_action(Packet *p)
{
  return p;
}

PushNullElement::PushNullElement()
{
}

PushNullElement::~PushNullElement()
{
}

  void
PushNullElement::push(int, Packet *p)
{
  output(0).push(p);
}


PullNullElement::PullNullElement()
{
}

PullNullElement::~PullNullElement()
{
}

  Packet *
PullNullElement::pull(int)
{
  Packet * p = input(0).pull();
  return p;
}

  CLICK_ENDDECLS
  EXPORT_ELEMENT(NullElement)
  EXPORT_ELEMENT(PushNullElement)
  EXPORT_ELEMENT(PullNullElement)
  ELEMENT_MT_SAFE(NullElement)
  ELEMENT_MT_SAFE(PushNullElement)
ELEMENT_MT_SAFE(PullNullElement)