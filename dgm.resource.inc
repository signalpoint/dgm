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
    return $result;
  }
  return NULL;
}

