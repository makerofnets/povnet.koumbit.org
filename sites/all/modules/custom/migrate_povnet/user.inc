<?php

/**
 * Mappings for Drupal 6 user migration.
 */
class UserMigration extends DrupalUser7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    //drupal_debug($row, 'UserMigration::prepareRow($row)');
  }
  public function prepare($entity, stdClass $row) {
    //drupal_debug($entity, 'UserMigration::prepare($entity)');
  }
  public function complete($entity, stdClass $row) {
    //drupal_debug($entity, 'UserMigration::complete($entity)');
  }
}
