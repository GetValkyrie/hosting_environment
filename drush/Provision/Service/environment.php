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
}
