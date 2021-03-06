<?php

/*
 * Defines the Saic Tweet class for migration processes.
 */

/**
 * The Rotator Image class is an extension of the Migration class,
 * representing distinct steps in a migration of the Rotator Image content type
 * process.  This will be Migration objects which actually import
 * data from a SAIC Drupal6 into a LEIDOS Drupal7  destination, 
 * By deriving classes directly from Migration class we will have other sorts of tasks 
 * of modules occur during the migration process.
 */
class saicRotatorImagesMigration extends Migration {

    // class constructor 
    public function __construct() {
        //parent constructor override 
        parent::__construct(MigrateGroup::getInstance('group3'));
        $this->description = t('Migrate Drupal6 SAIC Rotator Image content type into LEIDOS D7');

        //source definition
        // field definitions; 
        $source_fields = array(
            'nid' => t('Node NID'),
        );

        // Import rotator images nodes from the saic D6
        $query = db_select(SOURCE_DATABASE . '.node', 'n')
                ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
                ->condition('n.type', 'rotator_image', '=');
        // Join the revisions associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.node_revisions', 'nr', 'n.vid = nr.vid');
        $query->addField('nr', 'body');
        $query->addField('nr', 'teaser');

        // Join the user associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.users', 'u', 'n.uid = u.uid');
        $query->addField('u', 'name');

        // Join the data stored in the content type field associated with this announcement node(D6 table structure)
        $query->join(SOURCE_DATABASE . '.content_type_rotator_image', 'ri', 'n.nid = ri.nid');
        $query->addField('ri', 'field_rotator_image_fid');
        $query->addField('ri', 'field_rotator_image_list');
        $query->addField('ri', 'field_rotator_image_data');
        $query->addField('ri', 'field_rotator_image_caption_value');
        $query->addField('ri', 'field_rotator_image_description_value');
        $query->addField('ri', 'field_rotator_image_link_url');
        $query->addField('ri', 'field_rotator_image_link_title');
        $query->addField('ri', 'field_rotator_image_link_attributes');
        $query->addField('ri', 'field_rotator_target_value');
        $query->addField('ri', 'field_rotator_microsite_value');




//
//        $query->join(SOURCE_DATABASE . '.content_field_image_links', 'fil', 'n.vid = fil.vid');
//        $query->addField('fil', 'field_image_links_url');
//        $query->addField('fil', 'field_image_links_title');
//        $query->addField('fil', 'field_image_links_attributes');
//
//        $query->join(SOURCE_DATABASE . '.content_field_display_wall', 'fdw', 'n.vid = fdw.vid');
//        $query->addField('fdw', 'field_display_wall_value');





        $query->orderBy('n.nid', 'ASC');

        $this->source = new MigrateSourceSQL($query, $source_fields);

        //destination definition
        $this->destination = new MigrateDestinationNode('rotator_image');

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
        $this->addFieldMapping('field_rotator_image', 'field_rotator_image_fid');
        $this->addFieldMapping('field_rotator_image_link', 'field_rotator_image_link_url');
        $this->addFieldMapping('field_rotator_image_caption', 'field_rotator_image_caption_value');
        $this->addFieldMapping('field_rotator_image_description', 'field_rotator_image_description_value');
        $this->addFieldMapping('field_rotator_microsite', 'ield_rotator_target_value');
        $this->addFieldMapping('field_rotator_target', 'field_tweet_guid_value');



        //here we have anmapped fields
    }

    public function prepareRow($current_row) {
        /**
         *  @todo do some processing for this announcement , specifically with the links, thumbnail
         */
    }

}

?>
