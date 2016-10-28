<?php
/**
 * @file
 * povnet_content_types.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function povnet_content_types_taxonomy_default_vocabularies() {
  return array(
    'finding_help_issues' => array(
      'name' => 'Finding Help Issues',
      'machine_name' => 'finding_help_issues',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -6,
    ),
    'vocabulary_29' => array(
      'name' => 'Finding Help Tags',
      'machine_name' => 'vocabulary_29',
      'description' => 'For resources that may be directly helpful (service organizations, directories, how to\'s etc.). Make tags more refined then Issues, for ex: EI, Employment Insurance, pensions, etc.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -5,
    ),
    'vocabulary_3' => array(
      'name' => 'Location',
      'machine_name' => 'vocabulary_3',
      'description' => 'Choose the location which your information is relevant for. This will help others find it more easily.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -8,
    ),
    'vocabulary_30' => array(
      'name' => 'Research and Anaylsis Tags',
      'machine_name' => 'vocabulary_30',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 10,
    ),
    'vocabulary_32' => array(
      'name' => 'Resource Type',
      'machine_name' => 'vocabulary_32',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -10,
    ),
    'vocabulary_4' => array(
      'name' => 'Language',
      'machine_name' => 'vocabulary_4',
      'description' => 'If the post or resource is in a language other than English, or in English and another language please select the most applicable option.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 10,
    ),
    'vocabulary_5' => array(
      'name' => 'Issues',
      'machine_name' => 'vocabulary_5',
      'description' => 'Choose the issue(s) that best describe the topic(s) of this post. Use CTRL + click to select more than one issue.',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => -7,
    ),
    'vocabulary_7' => array(
      'name' => 'Find an Advocate: Type of Advocacy',
      'machine_name' => 'vocabulary_7',
      'description' => 'Choose the type(s) of advocacy this advocate/agency offers. Services must be pro-bono. Use CTRL + click to select more than one. This will help others find an advocacy service that meets their needs.',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 10,
    ),
    'vocabulary_9' => array(
      'name' => 'Using PovNet',
      'machine_name' => 'vocabulary_9',
      'description' => 'For articles and pages on how to use the PovNet site.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 10,
    ),
  );
}
