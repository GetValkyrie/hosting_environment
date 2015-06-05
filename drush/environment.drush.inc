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
  return array('environment' => 'environment');
}

/**
 * Implements drush_hook_post_COMMAND().
 */
function drush_environment_post_provision_install() {
  if (_environment_enabled()) {
    d()->service('environment')->post_install();
  }
}

function _environment_enabled() {
  return (
    d()->type == 'site' &&           // Environments only apply to sites.
    d()->profile != 'hostmaster' &&  // Let's be extra careful w/ Aegir.
    isset(d()->environment) &&
    !is_null(d()->environment)
  );
}

/**
 * Implements drush_hook_post_COMMAND().
 */
function drush_environment_post_provision_verify() {
  if (_environment_enabled()) {
    d()->service('environment')->post_verify();
  }
}

/**
 * Implements hook_provision_drupal_config().
 */
function environment_provision_drupal_config($uri, $data) {
  if (_environment_enabled()) {
    return d()->service('environment')->drupal_config($uri, $data);
  }
}
