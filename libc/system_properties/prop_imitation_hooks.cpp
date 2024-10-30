/*
 * Copyright (C) 2023 Paranoid Android
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <string.h>

#include "system_properties/prop_imitation_hooks.h"

#define GMS_UNSTABLE "com.google.android.gms.unstable"
#define PROP_ENABLED "persist.sys.pihooks.disable.gms_props"

#define PROP_SECURITY_PATCH "ro.build.version.security_patch"
#define PROP_PIH_SECURITY_PATCH "persist.sys.pihooks.security_patch"

#define PROP_FIRST_API_LEVEL "ro.product.first_api_level"
#define PROP_PIH_FIRST_API_LEVEL "persist.sys.pihooks.first_api_level"

void PropImitationHooks::OnFind(SystemProperties *props, const char** name) {
  if (getprogname() == nullptr || strcmp(getprogname(), GMS_UNSTABLE) != 0) {
    return;
  }
  if (!strcmp(*name, PROP_ENABLED) || IsDisabled(props)) {
    return;
  }
  PIH_LOG("name is %s", *name);
  if (strcmp(*name, PROP_SECURITY_PATCH) == 0) {
    *name = PROP_PIH_SECURITY_PATCH;
  } else if (strcmp(*name, PROP_FIRST_API_LEVEL) == 0) {
    *name = PROP_PIH_FIRST_API_LEVEL;
  } else {
    return;
  }
  PIH_LOG("name changed to %s", *name);
}

bool PropImitationHooks::IsDisabled(SystemProperties *props) {
  char value[PROP_VALUE_MAX];
  props->Get(PROP_ENABLED, value);
  return !strcmp(value, "true");
}
