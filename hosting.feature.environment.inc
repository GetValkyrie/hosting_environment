<?php


/**
 * @file
 * The hosting feature definition for environment.module integration.
 */

/**
 * Implements hook_hosting_feature().
 */
function hosting_environment_hosting_feature() {
  $features['environment'] = array(
    'title' => t('Environment'),
    'description' => t('Integration with the Environment module.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_environment',
    'group' => 'experimental',
  );
  return $features;
}
