<?php

/* * *
 * Defines the Saic Audio class for migration processes.
 */

/**
 * The Audio class is an extension of the Migration class,
 * representing distinct steps in a migration of the audio content type
 * process.  This will be Migration objects which actually import
 * data from a SAIC Drupal6 into a LEIDOS Drupal7  destination, 
 * By deriving classes directly from Migration class we will have other sorts of tasks 
 * of modules occur during the migration process.
 */
class saicAudiosMigration extends Migration {

    // class constructor 
    public function __construct() {
        //parent constructor override 
        parent::__construct(MigrateGroup::getInstance('group3'));
        $this->description = t('Migrate Drupal6 SAIC audio content type into LEIDOS D7');

        //source definition
        // field definitions; 
        $source_fields = array(
            'nid' => t('Node NID'),
        );

        // Import announcement nodes from the saic D6
        $query = db_select(SOURCE_DATABASE . '.node', 'n')
                ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
                ->condition('n.type', 'audio', '=');
        // Join the revisions associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.node_revisions', 'nr', 'n.vid = nr.vid');
        $query->addField('nr', 'body');
        $query->addField('nr', 'teaser');

        // Join the user associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.users', 'u', 'n.uid = u.uid');
        $query->addField('u', 'name');

        // Join the data stored in the content type field associated with this announcement node(D6 table structure)
        $query->join(SOURCE_DATABASE . '.content_type_audio', 'au', 'n.nid = au.nid');
        $query->addField('au', 'field_audio_short_description_value');
        $query->addField('au', 'field_audio_full_description_value');
        $query->addField('au', 'field_audio_cloudfront_url_value');
        $query->addField('au', 'field_audio_length_hour');
        $query->addField('au', 'field_audio_length_minute');
        $query->addField('au', 'field_audio_length_second');
        $query->addField('au', 'field_ddp_audio_guid_value');
        $query->addField('au', 'field_ddp_audio_ddpid_value');
        $query->addField('au', 'field_ddp_audio_updated_value');
        $query->addField('au', 'field_audio_thumbnail_fid');
        $query->addField('au', 'field_audio_thumbnail_list');
        $query->addField('au', 'field_audio_thumbnail_data');
        $query->addField('au', 'field_audio_http_url_value');

        // Join the data from custom field associated with this announcement node(D6 table structure)
        $query->join(SOURCE_DATABASE . '.content_field_audio_related_links', 'ar', 'n.vid = ar.vid');
        $query->addField('ar', 'field_audio_related_links_url');
        $query->addField('ar', 'field_audio_related_links_title');
        $query->addField('ar', 'field_audio_related_links_attributes');

        $query->join(SOURCE_DATABASE . '.content_field_display_wall', 'fd', 'n.vid = fd.vid');
        $query->addField('fd', 'field_display_wall_value');

        $query->orderBy('n.nid', 'ASC');

        $this->source = new MigrateSourceSQL($query, $source_fields);

        //destination definition
        $this->destination = new MigrateDestinationNode('audio');

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
        $this->addFieldMapping('field_audio_thumbnail', 'field_audio_thumbnail_fid');
        $this->addFieldMapping('field_audio_related_links', 'field_audio_related_links_url');
        $this->addFieldMapping('field_display_wall', 'field_display_wall_value');
        $this->addFieldMapping('field_audio_short_description', 'field_audio_short_description_value');
        $this->addFieldMapping('field_audio_full_description', 'field_audio_full_description_value');
        $this->addFieldMapping('field_audio_cloudfront_url', 'field_audio_cloudfront_url_value');
        $this->addFieldMapping('field_audio_http_url', 'field_audio_http_url_value');
        $this->addFieldMapping('field_audio_length', 'field_audio_length_second');
        $this->addFieldMapping('field_ddp_audio_guid', 'field_ddp_audio_guid_value');
        $this->addFieldMapping('field_ddp_audio_ddpid', 'field_ddp_audio_ddpid_value');
        $this->addFieldMapping(' field_ddp_audio_updated', 'field_ddp_audio_updated_value');


        //here we have anmapped fields
    }

    public function prepareRow($current_row) {
        /**
         *  @todo do some processing for this announcement , specifically with the links, thumbnail
         */
    }

}

?>
