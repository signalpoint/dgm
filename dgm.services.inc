<?php

function dgm_services_resources() {
  // Set up defaults.
  $file = array(
    'type' => 'inc',
    'module' => 'dgm',
    'name' => 'dgm.resource',
  );
  $access_callback = '_drupalgap_resource_access';
  $access_callback_file = array(
    'type' => 'inc',
    'module' => 'drupalgap',
    'name' => 'drupalgap.resource',
  );
  // Build resources.
  $resources = array(
    'dgm_resources' => array(
      'actions' => array(
        'project_download' => array(
          'help' => t('Returns data to download a project.'),
          'file' => $file,
          'access callback' => $access_callback,
          'access callback file' => $access_callback_file,
          'access arguments' => array('view published content'),
          'access arguments append' => TRUE,
          'callback' => 'dgm_project_download',
          'args' => array(
            array(
              'name'         => 'project_name',
              'type'         => 'string',
              'description'  => t('The project machine name.'),
              'source'       => array('data' => 'project_name'),
              'optional'     => FALSE,
            ),
          ),
        ),
      ),
    ),
  );
  return $resources;
}

