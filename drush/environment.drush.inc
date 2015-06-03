<?php

/**
 * @file
 * Code for integrating with the Environment module.
 */

/**
 * Implements hook_drush_init().
 */
function environment_drush_init() {
  environment_provision_register_autoload();
}

/**
 * Register our directory as a place to find provision classes.
 */
function environment_provision_register_autoload() {
  static $loaded = FALSE;
  if (!$loaded) {
    $loaded = TRUE;
    provision_autoload_register_prefix('Provision_', dirname(__FILE__));
  }
}

/**
 * Implements hook_provision_services().
 */
function environment_provision_services() {
  environment_provision_register_autoload();
  return array('environment' => NULL);
}

/**
 * Implements drush_hook_post_COMMAND().
 */
function drush_environment_post_provision_install() {
  drush_log('environment received from the frontend (d()->environment): ' . d()->environment);
}

/**
 * Implements drush_hook_post_COMMAND().
 */
function drush_environment_post_provision_verify() {
  drush_log('environment received from the frontend (d()->environment): ' . d()->environment);
}
