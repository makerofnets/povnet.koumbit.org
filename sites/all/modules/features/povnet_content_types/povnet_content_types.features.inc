<?php
/**
 * @file
 * povnet_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function povnet_content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function povnet_content_types_node_info() {
  $items = array(
    'apps' => array(
      'name' => t('Applications/Forms'),
      'base' => 'node_content',
      'description' => t('For applications and forms.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'article' => array(
      'name' => t('Article'),
      'base' => 'node_content',
      'description' => t('Articles in their simplest form.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'book' => array(
      'name' => t('Book page'),
      'base' => 'node_content',
      'description' => t('A <em>book page</em> is a page of content, organized into a collection of related entries collectively known as a <em>book</em>. A <em>book page</em> automatically displays links to adjacent pages, providing a simple navigation system for organizing and reviewing structured content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'event_new' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('For calendar.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'find_an_advocate' => array(
      'name' => t('Find An Advocate'),
      'base' => 'node_content',
      'description' => t('For Find An Advocate Listings.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'job' => array(
      'name' => t('Job'),
      'base' => 'node_content',
      'description' => t('For job postings.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'online_resource' => array(
      'name' => t('Online Resource'),
      'base' => 'node_content',
      'description' => t('For Online Resources'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => t('A static page, like a contact page or an about page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'webform' => array(
      'name' => t('Webform'),
      'base' => 'node_content',
      'description' => t('Create a new form or questionnaire accessible to users. Submission results and statistics are recorded and accessible to privileged users.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
