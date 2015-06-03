<?php

/**
 * @file
 * The Drush integration for Environment module.
 */

/**
 * Implements hook_hosting_site_context_options().
 */
function hosting_environment_hosting_site_context_options(&$task) {
  if (isset($task->ref->environment) && !empty($task->ref->environment)) {
    $task->context_options['environment'] = $task->ref->environment;
  }
  else {
    $task->context_options['environment'] = 'null';
  }
}

/**
 * Implements hook_drush_context_import().
 */
function hosting_environment_drush_context_import($context, &$node) {
  if ($context->type == 'site') {
    if (isset($context->environment) && !empty($context->environment)) {
      $node->environment = $context->environment;
    }
  }

}
