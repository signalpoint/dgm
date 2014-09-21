<?php

function dgm_project_download($project_name) {
  $query = db_select('node', 'n');
  $query->innerJoin(
    'field_data_field_project_machine_name',
    'pmn',
    'pmn.entity_id = n.nid AND pmn.revision_id = n.vid AND pmn.bundle = n.type'
  );
  $query->condition('n.type', 'project');
  $query->condition('pmn.field_project_machine_name_value', $project_name);
  $query->fields('n', array('nid'));
  $results = $query->execute();
  foreach($results as $row) {
    $project = node_load($row->nid);
    //return $project;
    if (!$project) { break; }
    $result = new stdClass();
    $result->title = $project->title;
    $result->field_project_sandbox = $project->field_project_sandbox['und'][0]['value'];
    $result->field_project_type = $project->field_project_type['und'][0]['value'];
    $result->field_project_machine_name = $project->field_project_machine_name['und'][0]['value'];
    $result->field_project_github_url = $project->field_project_github_url['und'][0]['url'];
    $parts = explode('/', $result->field_project_github_url);
    if (sizeof($parts) >= 5) {
      $owner = $parts[sizeof($parts) - 2];
      $repo = $parts[sizeof($parts) - 1];
      // Get cURL resource
      $curl = curl_init();
      // Set some options - we are passing in a useragent too here
      curl_setopt_array($curl, array(
          CURLOPT_RETURNTRANSFER => 1,
          CURLOPT_URL => 'https://api.github.com/repos/' .
            check_plain($owner) . '/' .
            check_plain($repo),
          CURLOPT_USERAGENT => 'Codular Sample cURL Request'
      ));
      // Send the request & save response to $resp
      $result->github = drupal_json_decode(curl_exec($curl));
      // Close request to clear up some resources
      curl_close($curl);
    }
    return $result;
  }
  return NULL;
}

