<?php

/**
 * Common mappings for the Drupal 6 node migrations.
 */
abstract class NodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->addFieldMapping(NULL, 'revision');
    $this->addFieldMapping(NULL, 'revision_uid');
    $this->addFieldMapping(NULL, 'log');
    $this->removeFieldMapping('pathauto');
    $this->addFieldMapping('pathauto')->defaultValue(1);
  }
}

class ApplicationsFormsMigration extends NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->addFieldMapping('field_more_info',          'field_additional_info');
    $this->addFieldMapping('field_more_info:format',   'field_additional_info:format');
    $this->addFieldMapping('field_organization',       'field_organization');
    $this->addFieldMapping('field_apps_about',         'field_apps_about');
    $this->addFieldMapping('field_apps_about:format',  'field_apps_about:format');
    $this->addFieldMapping('field_website',            'field_website');
    $this->addFieldMapping('field_website:title',      'field_website:title');
    $this->addFieldMapping('field_website:attributes', 'field_website:attributes');
    // taxonomy_vocabulary_3
    $this->addFieldMapping('taxonomy_vocabulary_3', 3)
          ->sourceMigration('Location');
    $this->addFieldMapping('taxonomy_vocabulary_3:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_4
    $this->addFieldMapping('taxonomy_vocabulary_4', 4)
          ->sourceMigration('Language');
    $this->addFieldMapping('taxonomy_vocabulary_4:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_5
    $this->addFieldMapping('taxonomy_vocabulary_5', 5)
          ->sourceMigration('Issues');
    $this->addFieldMapping('taxonomy_vocabulary_5:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_29
    $this->addFieldMapping('taxonomy_vocabulary_29', 29)
          ->sourceMigration('FindingHelpTags');
    $this->addFieldMapping('taxonomy_vocabulary_29:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_33
    $this->addFieldMapping('field_finding_help_issues', 33)
          ->sourceMigration('FindingHelpIssues');
    $this->addFieldMapping('field_finding_help_issues:source_type')
          ->defaultValue('tid');
    /*
    // field_image
    $this->addFieldMapping('field_image', 'field_image')
           ->sourceMigration('File');
    $this->addFieldMapping('field_image:title', 'field_image:title');
    $this->addFieldMapping('field_image:alt', 'field_image:alt');
    $this->addFieldMapping(NULL, 'field_image:list');
    $this->addFieldMapping('field_image:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_image:file_class')
           ->defaultValue('MigrateFileFid');
    */
    // field_upload
    $this->addFieldMapping(NULL, 'upload');
    $this->addFieldMapping(NULL, 'upload:description');
    $this->addFieldMapping(NULL, 'upload:list');
    $this->addFieldMapping(NULL, 'upload:weight');
  }
  protected function query() {
    $query = parent::query();
    // Join location table (works with location & location_cck)
    $query->leftJoin('location_instance', 'li', 'li.nid = n.nid AND li.vid = n.vid');
    $query->groupBy('n.nid');
    $query->addExpression('GROUP_CONCAT(lid)', 'lid');
    //drupal_debug((string) $query, 'ApplicationsFormsMigration::query($query)');
    return $query;
  }
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    // set of nid's from source site corresponding to types on source site for field_related_pages_apps
    // field_node_ref, field_node_ref2, field_node_ref3 -> field_related_pages_apps (apps->apps,find_an_advocate,online_resource)
    $query_result = db_select('migrate_map_applicationsforms', 'mm')
                ->fields('mm', array('sourceid1'))
                ->execute()
                ->fetchAllAssoc('sourceid1');
    $row->RelatedNodes['ApplicationsForms'] = array_keys($query_result);
    $query_result = db_select('migrate_map_findanadvocate', 'mm')
                ->fields('mm', array('sourceid1'))
                ->execute()
                ->fetchAllAssoc('sourceid1');
    $row->RelatedNodes['FindAnAdvocate'] = array_keys($query_result);
    $query_result = db_select('migrate_map_onlineresource', 'mm')
                ->fields('mm', array('sourceid1'))
                ->execute()
                ->fetchAllAssoc('sourceid1');
    $row->RelatedNodes['OnlineResource'] = array_keys($query_result);
    if ($row->lid) {
      $lids = explode(',', $row->lid);
      db_set_active('source');
      $locations_query = db_select('location', 'l');
      db_set_active();
      $locations_query->leftJoin('location_phone', 'lp', 'l.lid = lp.lid');
      $locations_query->leftJoin('location_fax', 'lf', 'l.lid = lf.lid');
      $locations_query->fields('l', array('lid', 'name', 'street', 'additional', 'city', 'province', 'postal_code', 'country'));
      $locations_query->fields('lp', array('phone'));
      $locations_query->fields('lf', array('fax'));
      $locations_query->condition('l.lid', $lids, 'IN');
      $locations_query->condition('l.country', 'xx', '!=');
      //drupal_debug((string) $locations_query, 'FindAnAdvocateMigration::prepare() $locations_query');
      $row->locations = $locations_query->execute()->fetchAllAssoc('lid');
      //drupal_debug($locations, 'FindAnAdvocateMigration::prepare() $locations');
    }
    else {
      $row->locations = array();
    }
    //drupal_debug($row, 'ApplicationsFormsMigration::prepareRow($row)');
  }
  public function prepare($entity, stdClass $row) {
    // find new nid's for entity reference field_related_pages_apps
    // passing an array to sourceMigration() is in theory supposed to do the following...
    if (isset($row->field_node_ref[0]['nid'])) {
      $missing = TRUE;
      foreach (array_keys($row->RelatedNodes) as $mySourceMigration) {
        if (in_array($row->field_node_ref[0], $row->RelatedNodes[$mySourceMigration])) {
          $result = parent::handleSourceMigration($mySourceMigration, $row->field_node_ref[0]);
          if ($result) {
            $entity->field_related_pages_apps[LANGUAGE_NONE][] = array('nid' => $result);
            $missing = FALSE;
            break;
          }
        }
      }
      if ($missing) { drupal_debug("no source migration found: field_node_ref source={$row->nid} target={$row->field_node_ref[0]}", "ApplicationsFormsMigration::prepare()"); }
    }
    if (isset($row->field_node_ref2[0]['nid'])) {
      $missing = TRUE;
      foreach (array_keys($row->RelatedNodes) as $mySourceMigration) {
        if (in_array($row->field_node_ref2[0], $row->RelatedNodes[$mySourceMigration])) {
          $result = parent::handleSourceMigration($mySourceMigration, $row->field_node_ref2[0]);
          if ($result) {
            $entity->field_related_pages_apps[LANGUAGE_NONE][] = array('nid' => $result);
            $missing = FALSE;
            break;
          }
        }
      }
      if ($missing) { drupal_debug("no source migration found: field_node_ref2 source={$row->nid} target={$row->field_node_ref2[0]}", "ApplicationsFormsMigration::prepare()"); }
    }
    if (isset($row->field_node_ref3[0]['nid'])) {
      $missing = TRUE;
      foreach (array_keys($row->RelatedNodes) as $mySourceMigration) {
        if (in_array($row->field_node_ref3[0], $row->RelatedNodes[$mySourceMigration])) {
          $result = parent::handleSourceMigration($mySourceMigration, $row->field_node_ref3[0]);
          if ($result) {
            $entity->field_related_pages_apps[LANGUAGE_NONE][] = array('nid' => $result);
            $missing = FALSE;
            break;
          }
        }
      }
      if ($missing) { drupal_debug("no source migration found: field_node_ref3 source={$row->nid} target={$row->field_node_ref3[0]}", "ApplicationsFormsMigration::prepare()"); }
    }
    foreach ($row->locations as $location) {
      $entity->field_address[LANGUAGE_NONE][] = array(
          'country' => 'CA',
          'administrative_area' => $location->province,
          'locality' => $location->city,
          'postal_code' => $location->postal_code,
          'thoroughfare' => $location->street,
          'premise' => $location->additional,
          'organisation_name' => $location->name,
          );
    }
    //drupal_debug($entity, 'ApplicationsFormsMigration::prepare($entity)');
  }
}

class ArticleMigration extends NodeMigration {
  public function __construct(array $arguments) {
    // Add any other data we're pulling into the source row, before the parent
    // constructor.
    //$this->sourceFields['summary'] = 'Summary string from D6';
    parent::__construct($arguments);
    $this->addFieldMapping(NULL,                        'field_audit');
    $this->addFieldMapping(NULL,                        'field_audit_notes');
    $this->addFieldMapping(NULL,                        'field_date_article');
    $this->addFieldMapping(NULL,                        'field_date_article_0');
    $this->addFieldMapping(NULL,                        'field_date_article_1');
    $this->addFieldMapping(NULL,                        'field_date_article_2');
    $this->addFieldMapping(NULL,                        'field_date_article_3');
    $this->addFieldMapping(NULL,                        'field_date_article_4');
    $this->addFieldMapping(NULL,                        'field_source_0');
    $this->addFieldMapping(NULL,                        'field_source_1');
    $this->addFieldMapping(NULL,                        'field_source_3');
    $this->addFieldMapping(NULL,                        'field_source_4');
    $this->addFieldMapping(NULL,                        'field_source_5');
    $this->addFieldMapping(NULL,                        'field_source_6');
    $this->addFieldMapping('field_image_by',            'field_image_by');
    $this->addFieldMapping('field_image_by:title',      'field_image_by:title');
    $this->addFieldMapping('field_image_by:attributes', 'field_image_by:attributes');
    $this->addFieldMapping('field_info1',               'field_info1');
    $this->addFieldMapping('field_info1:title',         'field_info1:title');
    $this->addFieldMapping('field_info1:attributes',    'field_info1:attributes');
    // field_image
    $this->addFieldMapping('field_image', 'field_image')
           ->sourceMigration('File');
    $this->addFieldMapping('field_image:title', 'field_image:title');
    $this->addFieldMapping('field_image:alt', 'field_image:alt');
    $this->addFieldMapping(NULL, 'field_image:list');
    $this->addFieldMapping('field_image:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_image:file_class')
           ->defaultValue('MigrateFileFid');
    $this->addFieldMapping(NULL, 2);
    // taxonomy_vocabulary_3
    $this->addFieldMapping('taxonomy_vocabulary_3', 3)
          ->sourceMigration('Location');
    $this->addFieldMapping('taxonomy_vocabulary_3:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_4
    $this->addFieldMapping('taxonomy_vocabulary_4', 4)
          ->sourceMigration('Language');
    $this->addFieldMapping('taxonomy_vocabulary_4:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_5
    $this->addFieldMapping('taxonomy_vocabulary_5', 5)
          ->sourceMigration('Issues');
    $this->addFieldMapping('taxonomy_vocabulary_5:source_type')
          ->defaultValue('tid');
    // field_upload
    $this->addFieldMapping('field_upload', 'upload')
           ->sourceMigration('File');
    $this->addFieldMapping('field_upload:description', 'upload:description');
    $this->addFieldMapping('field_upload:display', 'upload:list');
    $this->addFieldMapping(NULL, 'upload:weight');
    $this->addFieldMapping('field_upload:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_upload:file_class')
           ->defaultValue('MigrateFileFid');
  }
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    // more info fields
    if ($link = ArticleMigration::_extract_link($row->field_more_info2)) {
      $row->field_info1[] = $link['link'];
      $row->{'field_info1:title'}[] = $link['title'];
      $row->{'field_info1:attributes'}[] = 'a:0:{}';
    }
    if ($link = ArticleMigration::_extract_link($row->field_more_info3)) {
      $row->field_info1[] = $link['link'];
      $row->{'field_info1:title'}[] = $link['title'];
      $row->{'field_info1:attributes'}[] = 'a:0:{}';
    }
    if ($link = ArticleMigration::_extract_link($row->field_more_info4)) {
      $row->field_info1[] = $link['link'];
      $row->{'field_info1:title'}[] = $link['title'];
      $row->{'field_info1:attributes'}[] = 'a:0:{}';
    }
    if ($link = ArticleMigration::_extract_link($row->field_more_info5)) {
      $row->field_info1[] = $link['link'];
      $row->{'field_info1:title'}[] = $link['title'];
      $row->{'field_info1:attributes'}[] = 'a:0:{}';
    }
    if ($link = ArticleMigration::_extract_link($row->field_more_info6)) {
      $row->field_info1[] = $link['link'];
      $row->{'field_info1:title'}[] = $link['title'];
      $row->{'field_info1:attributes'}[] = 'a:0:{}';
    }
    if ($link = ArticleMigration::_extract_link($row->field_more_info_1)) {
      $row->field_info1[] = $link['link'];
      $row->{'field_info1:title'}[] = $link['title'];
      $row->{'field_info1:attributes'}[] = 'a:0:{}';
    }
    if (isset($row->field_info1) && array_key_exists(0, $row->field_info1) && !$row->field_info1[0]) {
      unset($row->field_info1[0]);
      unset($row->{'field_info1:title'}[0]);
      unset($row->{'field_info1:attributes'}[0]);
    }
    // set of nid's from source site corresponding to types on source site for field_related_pages_apps
    // field_node_ref, field_node_ref2, field_node_ref3 -> field_related_pages_articles (article->apps,article,event_new,find_an_advocate,online_resource)
    $query_result = db_select('migrate_map_applicationsforms', 'mm')
                ->fields('mm', array('sourceid1'))
                ->execute()
                ->fetchAllAssoc('sourceid1');
    $row->RelatedNodes['ApplicationsForms'] = array_keys($query_result);
    $query_result = db_select('migrate_map_findanadvocate', 'mm')
                ->fields('mm', array('sourceid1'))
                ->execute()
                ->fetchAllAssoc('sourceid1');
    $row->RelatedNodes['FindAnAdvocate'] = array_keys($query_result);
    $query_result = db_select('migrate_map_onlineresource', 'mm')
                ->fields('mm', array('sourceid1'))
                ->execute()
                ->fetchAllAssoc('sourceid1');
    $row->RelatedNodes['OnlineResource'] = array_keys($query_result);
    $query_result = db_select('migrate_map_article', 'mm')
                ->fields('mm', array('sourceid1'))
                ->execute()
                ->fetchAllAssoc('sourceid1');
    $row->RelatedNodes['Article'] = array_keys($query_result);
    //drupal_debug($row, 'ArticleMigration::prepareRow($row)');
  }
  public function prepare($entity, stdClass $row) {
    // find new nid's for entity reference field_related_pages_articles
    // passing an array to sourceMigration() is in theory supposed to do the following...
    if (isset($row->field_node_ref[0]['nid'])) {
      $missing = TRUE;
      foreach (array_keys($row->RelatedNodes) as $mySourceMigration) {
        if (in_array($row->field_node_ref[0], $row->RelatedNodes[$mySourceMigration])) {
          $result = parent::handleSourceMigration($mySourceMigration, $row->field_node_ref[0]);
          if ($result) {
            $entity->field_related_pages_articles[LANGUAGE_NONE][] = array('nid' => $result);
            $missing = FALSE;
            break;
          }
        }
      }
      if ($missing) { drupal_debug("no source migration found: field_node_ref source={$row->nid} target={$row->field_node_ref[0]}", "ArticleMigration::prepare()"); }
    }
    if (isset($row->field_node_ref2[0]['nid'])) {
      $missing = TRUE;
      foreach (array_keys($row->RelatedNodes) as $mySourceMigration) {
        if (in_array($row->field_node_ref2[0], $row->RelatedNodes[$mySourceMigration])) {
          $result = parent::handleSourceMigration($mySourceMigration, $row->field_node_ref2[0]);
          if ($result) {
            $entity->field_related_pages_articles[LANGUAGE_NONE][] = array('nid' => $result);
            $missing = FALSE;
            break;
          }
        }
      }
      if ($missing) { drupal_debug("no source migration found: field_node_ref2 source={$row->nid} target={$row->field_node_ref2[0]}", "ArticleMigration::prepare()"); }
    }
    if (isset($row->field_node_ref3[0]['nid'])) {
      $missing = TRUE;
      foreach (array_keys($row->RelatedNodes) as $mySourceMigration) {
        if (in_array($row->field_node_ref3[0], $row->RelatedNodes[$mySourceMigration])) {
          $result = parent::handleSourceMigration($mySourceMigration, $row->field_node_ref3[0]);
          if ($result) {
            $entity->field_related_pages_articles[LANGUAGE_NONE][] = array('nid' => $result);
            $missing = FALSE;
            break;
          }
        }
      }
      if ($missing) { drupal_debug("no source migration found: field_node_ref3 source={$row->nid} target={$row->field_node_ref3[0]}", "ArticleMigration::prepare()"); }
    }
    //drupal_debug($entity, 'ArticleMigration::prepare($entity)');
  }
  public function _extract_link($link) {
    if (preg_match('@<a href="(http[^"]*)"[^>]*>(.*?)</a>@', $link, $matches)) {
      return array('link' => $matches[1], 'title' => strip_tags($matches[2]));
    }
    return FALSE;
  }
}

class FindAnAdvocateMigration extends NodeMigration {
  public function __construct(array $arguments) {
    // Add any other data we're pulling into the source row, before the parent
    // constructor.
    //$this->sourceFields['summary'] = 'Summary string from D6';
    parent::__construct($arguments);
    $this->addFieldMapping('field_website',              'field_website');
    $this->addFieldMapping('field_website:title',        'field_website:title');
    $this->addFieldMapping('field_website:attributes',   'field_website:attributes');
    $this->addFieldMapping('field_telephone',            'field_telephone');
    $this->addFieldMapping(NULL,                         'field_other_tel');
    $this->addFieldMapping('field_toll_free_tel',        'field_toll_free_tel');
    $this->addFieldMapping('field_fax',                  'field_fax');
    $this->addFieldMapping('field_hours',                'field_hours');
    $this->addFieldMapping('field_hours:format',         'field_hours:format');
    $this->addFieldMapping('field_email',                'field_email');
    $this->addFieldMapping(NULL,                         'field_email:format');
    $this->addFieldMapping('field_advocacy_desc',        'field_advocacy_desc');
    $this->addFieldMapping('field_advocacy_desc:format', 'field_advocacy_desc:format');
    // field_image
    $this->addFieldMapping('field_image', 'field_image')
           ->sourceMigration('File');
    $this->addFieldMapping('field_image:title', 'field_image:title');
    $this->addFieldMapping('field_image:alt', 'field_image:alt');
    $this->addFieldMapping(NULL, 'field_image:list');
    $this->addFieldMapping('field_image:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_image:file_class')
           ->defaultValue('MigrateFileFid');
    // taxonomy_vocabulary_4
    $this->addFieldMapping('taxonomy_vocabulary_4', 4)
          ->sourceMigration('Language');
    $this->addFieldMapping('taxonomy_vocabulary_4:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_7
    $this->addFieldMapping('taxonomy_vocabulary_7', 7)
          ->sourceMigration('TypeOfAdvocacy');
    $this->addFieldMapping('taxonomy_vocabulary_7:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_29
    $this->addFieldMapping('taxonomy_vocabulary_29', 29)
          ->sourceMigration('FindingHelpTags');
    $this->addFieldMapping('taxonomy_vocabulary_29:source_type')
          ->defaultValue('tid');
    $this->addFieldMapping(NULL, 15);
    $this->addFieldMapping(NULL, 16);
    $this->addFieldMapping(NULL, 17);
    $this->addFieldMapping(NULL, 18);
    $this->addFieldMapping(NULL, 19);
    $this->addFieldMapping(NULL, 20);
    $this->addFieldMapping(NULL, 21);
    $this->addFieldMapping(NULL, 22);
    $this->addFieldMapping(NULL, 23);
    $this->addFieldMapping(NULL, 24);
    $this->addFieldMapping(NULL, 25);
    $this->addFieldMapping(NULL, 26);
    $this->addFieldMapping(NULL, 27);
    $this->addFieldMapping(NULL, 28);
  }
  protected function query() {
    $query = parent::query();
    // Join location table (works with location & location_cck)
    $query->leftJoin('location_instance', 'li', 'li.nid = n.nid AND li.vid = n.vid');
    $query->groupBy('n.nid');
    $query->addExpression('GROUP_CONCAT(lid)', 'lid');
    //drupal_debug((string) $query, 'FindAnAdvocateMigration::query($query)');
    return $query;
  }
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    if ($row->field_telephone) {
      $row->field_telephone = array($row->field_telephone);
    }
    else {
      $row->field_telephone = array();
    }
    if ($row->field_other_tel) {
      $row->field_telephone[] = $row->field_other_tel;
    }
    if ($row->lid) {
      $lids = explode(',', $row->lid);
      db_set_active('source');
      $locations_query = db_select('location', 'l');
      db_set_active();
      $locations_query->leftJoin('location_phone', 'lp', 'l.lid = lp.lid');
      $locations_query->leftJoin('location_fax', 'lf', 'l.lid = lf.lid');
      $locations_query->fields('l', array('lid', 'name', 'street', 'additional', 'city', 'province', 'postal_code', 'country'));
      $locations_query->fields('lp', array('phone'));
      $locations_query->fields('lf', array('fax'));
      $locations_query->condition('l.lid', $lids, 'IN');
      $locations_query->condition('l.country', 'xx', '!=');
      //drupal_debug((string) $locations_query, 'FindAnAdvocateMigration::prepare() $locations_query');
      $row->locations = $locations_query->execute()->fetchAllAssoc('lid');
      //drupal_debug($locations, 'FindAnAdvocateMigration::prepare() $locations');
    }
    else {
      $row->locations = array();
    }
    //drupal_debug($row, 'FindAnAdvocateMigration::prepareRow($row)');
  }
  public function prepare($entity, stdClass $row) {
    foreach ($row->locations as $location) {
      $entity->field_address[LANGUAGE_NONE][] = array(
          'country' => 'CA',
          'administrative_area' => $location->province,
          'locality' => $location->city,
          'postal_code' => $location->postal_code,
          'thoroughfare' => $location->street,
          'premise' => $location->additional,
          'organisation_name' => $location->name,
          );
      if ($location->phone) {
        $entity->field_telephone[LANGUAGE_NONE][] = array(
            'value' => $location->name . ': ' . $location->phone,
            );
      }
      if ($location->fax) {
        $entity->field_fax[LANGUAGE_NONE][] = array(
            'value' => $location->name . ': ' . $location->fax,
            );
      }
    }
    //drupal_debug($entity, 'FindAnAdvocateMigration::prepare($entity)');
  }
}

class OnlineResourceMigration extends NodeMigration {
  public function __construct(array $arguments) {
    // Add any other data we're pulling into the source row, before the parent
    // constructor.
    //$this->sourceFields['summary'] = 'Summary string from D6';
    parent::__construct($arguments);
    $this->addFieldMapping('field_about',               'field_about');
    $this->addFieldMapping('field_about:format',        'field_about:format');
    $this->addFieldMapping('field_website',             'field_website');
    $this->addFieldMapping('field_website:title',       'field_website:title');
    $this->addFieldMapping('field_website:attributes',  'field_website:attributes');
    $this->addFieldMapping('field_source',              'field_source');
    $this->addFieldMapping('field_source:title',        'field_source:title');
    $this->addFieldMapping('field_source:attributes',   'field_source:attributes');
    // field_image
    $this->addFieldMapping('field_image', 'field_image')
           ->sourceMigration('File');
    $this->addFieldMapping('field_image:title', 'field_image:title');
    $this->addFieldMapping('field_image:alt', 'field_image:alt');
    $this->addFieldMapping(NULL, 'field_image:list');
    $this->addFieldMapping('field_image:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_image:file_class')
           ->defaultValue('MigrateFileFid');
    // field_upload
    $this->addFieldMapping('field_upload', 'upload')
           ->sourceMigration('File');
    $this->addFieldMapping('field_upload:description', 'upload:description');
    $this->addFieldMapping('field_upload:display', 'upload:list');
    $this->addFieldMapping(NULL, 'upload:weight');
    $this->addFieldMapping('field_upload:preserve_files')
         ->defaultValue(TRUE);
    $this->addFieldMapping('field_upload:file_class')
           ->defaultValue('MigrateFileFid');
    // taxonomy_vocabulary_3
    $this->addFieldMapping('taxonomy_vocabulary_3', 3)
          ->sourceMigration('Location');
    $this->addFieldMapping('taxonomy_vocabulary_3:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_4
    $this->addFieldMapping('taxonomy_vocabulary_4', 4)
          ->sourceMigration('Language');
    $this->addFieldMapping('taxonomy_vocabulary_4:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_5
    $this->addFieldMapping('taxonomy_vocabulary_5', 5)
          ->sourceMigration('Issues');
    $this->addFieldMapping('taxonomy_vocabulary_5:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_29
    $this->addFieldMapping('taxonomy_vocabulary_29', 29)
          ->sourceMigration('FindingHelpTags');
    $this->addFieldMapping('taxonomy_vocabulary_29:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_30
    $this->addFieldMapping('taxonomy_vocabulary_30', 30)
          ->sourceMigration('ResearchAndAnalysisTags');
    $this->addFieldMapping('taxonomy_vocabulary_30:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_32
    $this->addFieldMapping('taxonomy_vocabulary_32', 32)
          ->sourceMigration('ResourceType');
    $this->addFieldMapping('taxonomy_vocabulary_32:source_type')
          ->defaultValue('tid');
    // taxonomy_vocabulary_33
    $this->addFieldMapping('field_finding_help_issues', 33)
          ->sourceMigration('FindingHelpIssues');
    $this->addFieldMapping('field_finding_help_issues:source_type')
          ->defaultValue('tid');
  }
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    //drupal_debug($row, 'OnlineResourceMigration::prepareRow($row)');
  }
  public function prepare($entity, stdClass $row) {
    if (isset($row->field_node_ref[0]['nid'])) {
      $result = parent::handleSourceMigration('OnlineResource', $row->field_node_ref[0]);
      if ($result) {
        $entity->field_related_pages_resources[LANGUAGE_NONE][] = array('nid' => $result);
        //drupal_debug($result, 'OnlineResourceMigration::prepare($result)');
      }
      else {
        drupal_debug("no source migration found: field_node_ref source={$row->nid} target={$row->field_node_ref[0]}", "OnlineResourceMigration::prepare()");
      }
    }
    if (isset($row->field_node_ref2[0]['nid'])) {
      $result = parent::handleSourceMigration('OnlineResource', $row->field_node_ref2[0]);
      if ($result) {
        $entity->field_related_pages_resources[LANGUAGE_NONE][] = array('nid' => $result);
        //drupal_debug($result, 'OnlineResourceMigration::prepare($result2)');
      }
      else {
        drupal_debug("no source migration found: field_node_ref2 source={$row->nid} target={$row->field_node_ref2[0]}", "OnlineResourceMigration::prepare()");
      }
    }
    //drupal_debug($entity, 'OnlineResourceMigration::prepare($entity)');
  }
}
