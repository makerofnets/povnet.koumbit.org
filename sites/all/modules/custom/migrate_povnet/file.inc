<?php

/**
 * Image-specific mappings and handling.
 */
class FileMigration extends DrupalFile6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    //drupal_debug($row, 'FileMigration::prepareRow($row');
  }
}
