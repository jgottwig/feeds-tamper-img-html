<?php

/**
 * @file
 *   Simple plugin that grabs the first image from a chunk of HTML
 */

$plugin = array(
  'form' => 'tamper_image_form',
  'callback' => 'tamper_image_callback',
  'name' => 'First Image',
  'category' => 'HTML',
);

function tamper_image_form($importer, $element_key, $settings) {
  $form = array();
  $form['help']['#value'] = t('This simply accepts a chunk of HTML and returns the first image from an img tag');
  return $form;
}

/**
 * Check HTML Dom for image
 */
function tamper_image_callback($source, $item_key, $element_key, &$field, $settings) {
  $data = html_entity_decode($field);		// You might not need this
  $dom = new DOMDocument;
  $dom->loadHTML($data);
  $dom->preserveWhiteSpace = false;
  $images = $dom->getElementsByTagName('img');
  $output = array();
  foreach ($images as $image) {
    $output[] = $image->getAttribute('src');
  }
  $field = reset($output);
}
