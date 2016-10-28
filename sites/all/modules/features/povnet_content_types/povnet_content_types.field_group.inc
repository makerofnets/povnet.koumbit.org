<?php
/**
 * @file
 * povnet_content_types.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function povnet_content_types_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_telephone|node|find_an_advocate|form';
  $field_group->group_name = 'group_telephone';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'find_an_advocate';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Telephone',
    'weight' => '4',
    'children' => array(
      0 => 'field_fax',
      1 => 'field_telephone',
      2 => 'field_toll_free_tel',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-telephone field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_telephone|node|find_an_advocate|form'] = $field_group;

  return $export;
}
