<?php

/**
 * @file
 * Support for the Metatag module.
 * @todo find usage and migrate the nodeword to metatags
 */

/**
 * Destination handler.
 */
class MigrateMetatagHandler extends MigrateDestinationHandler {

    public function __construct() {
        $this->registerTypes(array('node', 'user', 'taxonomy_term'));
    }

    /**
     * Make the destination field visible.
     */
    public function fields() {
        $fields = array();
        $fields['meta_description'] = t('Meta Tag Description');
        $fields['meta_keywords'] = t('Meta Tag Keywords');
        $fields['meta_title'] = t('Meta Tag Title');

        return $fields;
    }

    public function prepare($entity, stdClass $row) {
        if (isset($entity->meta_description)) {
            $entity->metatags['description']['value'] = $entity->meta_description;
            unset($entity->meta_description);
        }
        if (isset($entity->meta_keywords)) {
            $entity->metatags['keywords']['value'] = $entity->meta_keywords;
            unset($entity->meta_keywords);
        }
        if (isset($entity->meta_title)) {
            $entity->metatags['title']['value'] = $entity->meta_title;
            unset($entity->meta_title);
        }
    }

}