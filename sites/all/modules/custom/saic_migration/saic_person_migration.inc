<?php

/*
 * Defines the Person class for migration processes.
 */

/**
 * The Person class is an extension of the Migration class,
 * representing distinct steps in a migration of the Person content type
 * process.  This will be Migration objects which actually import
 * data from a SAIC Drupal6 into a LEIDOS Drupal 7 destination, 
 * By deriving classes directly from Migration class we will have other sorts of tasks 
 * of modules occur during the migration process.
 */
class saicPersonsMigration extends Migration {

    // class constructor 
    public function __construct() {
        //parent constructor override 
        parent::__construct(MigrateGroup::getInstance('group3'));
        $this->description = t('Migrate Drupal6 SAIC Person content type into LEIDOS D7');

        //source definition
        // field definitions; 
        $source_fields = array(
            'nid' => t('Node NID'),
        );

        // Import resource  nodes from the saic D6
        $query = db_select(SOURCE_DATABASE . '.node', 'n')
                ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
                ->condition('n.type', 'person', '=');
        // Join the revisions associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.node_revisions', 'nr', 'n.vid = nr.vid');
        $query->addField('nr', 'body');
        $query->addField('nr', 'teaser');

        // Join the user associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.users', 'u', 'n.uid = u.uid');
        $query->addField('u', 'name');

        // Join the data stored in the content type field associated with this announcement node(D6 table structure)
        $query->join(SOURCE_DATABASE . '.content_type_person', 'tp', 'n.nid = tp.nid');
        $query->addField('tp', 'field_person_title_value');
        $query->addField('tp', 'field_person_department_value');
        $query->addField('pr', 'field_person_content_bottom_value');
        $query->addField('pr', 'field_person_portrait_fid');
        $query->addField('pr', 'field_person_portrait_list');
        $query->addField('pr', 'field_person_portrait_data');

        $query->addField('tp', 'field_hi_res_portrait_url');
        $query->addField('tp', 'field_hi_res_portrait_title');
        $query->addField('pr', 'field_hi_res_portrait_attributes');
        $query->addField('pr', 'field_person_pdf_biography_fid');
        $query->addField('pr', 'field_person_pdf_biography_list');
        $query->addField('pr', 'field_person_pdf_biography_data');

        $query->addField('tp', 'field_person_making_a_difference_value');
        $query->addField('tp', 'field_person_making_a_difference_format');
        $query->addField('pr', 'field_person_areas_and_work_value');
        $query->addField('pr', 'field_person_areas_and_work_format');

//
//        $query->join(SOURCE_DATABASE . '.content_field_image_links', 'fil', 'n.vid = fil.vid');
//        $query->addField('fil', 'field_image_links_url');
//        $query->addField('fil', 'field_image_links_title');
//        $query->addField('fil', 'field_image_links_attributes');
//
        $query->join(SOURCE_DATABASE . '.content_field_person_media', 'pm', 'n.vid = pm.vid');
        $query->addField('pm', 'field_person_media_nid');

        $query->join(SOURCE_DATABASE . '.content_field_page_breadcrumb', 'fbk', 'n.vid = fbk.vid');
        $query->addField('fbk', 'field_page_breadcrumb_value');

        $query->join(SOURCE_DATABASE . '.content_field_page_left_menu', 'lm', 'n.vid = lm.vid');
        $query->addField('lm', 'field_page_left_menu_value');

        $query->join(SOURCE_DATABASE . '.content_field_news_external_link', 'ext', 'n.vid = ext.vid');
        $query->addField('ext', 'field_news_external_link_url');

        $query->orderBy('n.nid', 'ASC');

        $this->source = new MigrateSourceSQL($query, $source_fields);

        //destination definition
        $this->destination = new MigrateDestinationNode('person');

        // mapping 
        $this->map = new MigrateSQLMap($this->machineName, array(
            'nid' => array(
                'type' => 'int',
                'unsigned' => TRUE,
                'not null' => TRUE,
                'description' => 'D6 Unique User ID',
                'alias' => 'n',
            )
                ), MigrateDestinationNode::getKeySchema()
        );

        // Create the field mappings
        $this->addFieldMapping('is_new')->defaultValue(TRUE);
        $this->addFieldMapping('nid', 'nid');
        $this->addFieldMapping('vid', 'vid');
        $this->addFieldMapping('type', 'type');
        $this->addFieldMapping('language', 'language');
        $this->addFieldMapping('title', 'title');
        $this->addFieldMapping('uid', 'uid');
        $this->addFieldMapping('status', 'status');
        $this->addFieldMapping('created', 'created');
        $this->addFieldMapping('changed', 'changed');
        $this->addFieldMapping('comment', 'comment');
        $this->addFieldMapping('promote', 'promote');
        $this->addFieldMapping('moderate', 'moderate');
        $this->addFieldMapping('sticky', 'sticky');
        $this->addFieldMapping('tnid', 'tnid');
        $this->addFieldMapping('translate', 'translate');
        $this->addFieldMapping('body', 'body');
        $this->addFieldMapping('body:summary', 'teaser');


        // custom field mappping 
        $this->addFieldMapping('field_person_title', 'field_person_title_value');
        $this->addFieldMapping('field_person_department', 'field_person_department_value');
        $this->addFieldMapping('field_person_content_bottom', 'field_person_content_bottom_value');
        $this->addFieldMapping('field_person_teaser', 'field_person_teaser_value');

        $this->addFieldMapping('field_person_media', 'field_person_media_nid');
        $this->addFieldMapping('field_person_portrait', 'field_person_portrait_fid');
        $this->addFieldMapping('field_hi_res_portrait', 'field_hi_res_portrait_url');

        $this->addFieldMapping('field_person_pdf_biography', 'field_person_pdf_biography_fid');
        $this->addFieldMapping('field_person_making_a_difference', 'field_person_making_a_difference_value');
        $this->addFieldMapping('field_person_areas_and_work', 'field_person_areas_and_work_value');

        $this->addFieldMapping('field_page_left_menu', 'field_page_left_menu_value');
        $this->addFieldMapping('field_page_breadcrumb', 'field_page_left_menu_value');


        //here we have anmapped fields
    }

    public function prepareRow($current_row) {
        /**
         *  @todo do some processing for this announcement , specifically with the links, thumbnail
         */
    }

}

?>
