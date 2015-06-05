<?php

/**
 * The environment service class.
 */
class Provision_Service_environment extends Provision_Service {
  public $service = 'environment';

  /**
   * Add the needed properties to the site context.
   */
  static function subscribe_site($context) {
    $context->setProperty('environment');
  }

  /**
   * Wrapper around drush_HOOK_post_provision_install().
   */
  function post_install() {
    $this->post_verify();
  }

  /**
   * Wrapper around drush_HOOK_post_provision_verify().
   */
  function post_verify() {
    if (module_exists('environment')) {
      $env = $this->get_environment();
      drush_log(dt('Setting site environment to %env', array('%env' => $env)));
      // 'env-switch' will need the '--force' flag to allow it to run even if the
      // current environment already matches the one we're trying to set it to.
      // We'll set this option back to it's original value afterwards, so we save
      // that here.
      $orig_force = drush_get_option('force', FALSE);
      drush_set_option('force', TRUE);
      $result = drush_invoke('env-switch', array($env));
      drush_set_option('force', $orig_force);
      if ($result === FALSE) {
        // Something went wrong; provide some help in resolving it.
        drush_log(dt('The Environment module must be enabled on the site, and the `%env` environment must be defined.', array('%env' => $env)), 'error');
      }
    }
    else {
      drush_log(dt('The Environment module is not enabled on this site. The environment setting will therefore have no effect.'), 'warning');
    }
  }

  /**
   * Wrapper around hook_provision_drupal_config().
   */
  function drupal_config($uri, $data) {
    drush_log('Injecting environment name into site settings.php');
    $lines = array();
    $lines[] = "  \$conf['environment'] = '" . $this->get_environment() . "';";
    return implode("\n", $lines);
  }

  /**
   * Helper function to return the environment name.
   */
  function get_environment() {
    return d()->environment;
  }

}

class Provision_Service_environment_environment extends Provision_Service_environment {
  // Default sub-class, instantiated by d()->service('environment').
}
