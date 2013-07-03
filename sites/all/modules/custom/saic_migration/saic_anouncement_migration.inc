<?php

/* * *
 * Defines the announcement class for migration processes.
 */

/**
 * The announcement class is an extension of the Migration class,
 * representing distinct steps in a migration of the announcement content type
 * process.  This will be Migration objects which actually import
 * data from a SAIC Drupal6 into a LEIDOS Drupal7  destination, 
 * By deriving classes directly from Migration class we will have other sorts of tasks 
 * of modules) occur during the migration process.
 */
class saicAnnouncementsMigration extends Migration {

    // class constructor 
    public function __construct() {
        //parent constructor override 
        parent::__construct(MigrateGroup::getInstance('group3'));
        $this->description = t('Migrate Drupal6 SAIC announcement content type to LEIDOS D7');

        //source definition
        // field definitions; 
        $source_fields = array(
            'nid' => t('Node NID'),
        );

        // Import announcement nodes from the saic D6
        $query = db_select(SOURCE_DATABASE . '.node', 'n')
                ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
                ->condition('n.type', 'announcement', '=');
        // Join the revisions associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.node_revisions', 'nr', 'n.vid = nr.vid');
        $query->addField('nr', 'body');
        $query->addField('nr', 'teaser');

        // Join the user associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.users', 'u', 'n.uid = u.uid');
        $query->addField('u', 'name');

        // Join the data stored in the content type field associated with this announcement node(D6 table structure)
        $query->join(SOURCE_DATABASE . '.content_type_announcement', 'a', 'n.nid = a.nid');
        $query->addField('a', 'field_announcement_date_value');
        $query->addField('a', 'field_announcement_teaser_value');
        $query->addField('a', 'field_announcement_contact_value');
        $query->addField('a', 'field_announcement_contact_format');

        // Join the data from custom field associated with this announcement node(D6 table structure)
        $query->join(SOURCE_DATABASE . '.content_field_page_layout', 'pl', 'n.vid = pl.vid');
        $query->addField('pl', 'field_page_layout_value');

        $query->join(SOURCE_DATABASE . '.content_field_page_breadcrumb', 'pb', 'n.vid = pb.vid');
        $query->addField('pb', 'field_page_breadcrumb_value');

        $query->join(SOURCE_DATABASE . '.content_field_page_left_menu', 'lm', 'n.vid = lm.vid');
        $query->addField('lm', 'field_page_left_menu_value');

        $query->join(SOURCE_DATABASE . '.content_field_disclaimer', 'fd', 'n.vid = fd.vid');
        $query->addField('fd', 'field_disclaimer_nid');

        $query->join(SOURCE_DATABASE . '.content_field_parent_menu', 'pm', 'n.vid = pm.vid');
        $query->addField('pm', 'field_parent_menu_value');

        $query->join(SOURCE_DATABASE . '.content_field_news_external_link', 'ext', 'n.vid = ext.vid');
        $query->addField('ext', 'field_news_external_link_url');
        $query->addField('ext', 'field_news_external_link_title');
        $query->addField('ext', 'field_news_external_link_attributes');




        $query->orderBy('n.nid', 'ASC');

        $this->source = new MigrateSourceSQL($query, $source_fields);

        //destination definition
        $this->destination = new MigrateDestinationNode('announcement');

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
        $this->addFieldMapping('field_announcement_date', 'field_announcement_date_value');
        $this->addFieldMapping('field_announcement_teaser', 'field_announcement_teaser_value');

        $this->addFieldMapping('field_page_layout', 'content_field_page_layout');
        $this->addFieldMapping('field_page_left_menu', 'field_page_left_menu_value');
        $this->addFieldMapping('field_page_breadcrumb', 'field_page_breadcrumb_value');
        $this->addFieldMapping('field_disclaimer', 'field_disclaimer_nid');
        $this->addFieldMapping('field_parent_menu', 'field_parent_menu_value');

        $this->addFieldMapping('field_news_external_link', 'field_news_external_link_url');
        $this->addFieldMapping('field_news_external_link:title', 'field_news_external_link_title');
        $this->addFieldMapping('field_announcement_contact:attributes', 'field_news_external_link_attributes');

        $this->addFieldMapping(' field_announcement_contact', 'field_announcement_contact_value');

        $this->addFieldMapping('field_taxonomy', 'field_news_external_link_attributes');
        $this->addFieldMapping('field_workflow', 'field_news_external_link_attributes');

        //here we have anmapped fields
    }

    public function prepareRow($current_row) {
        /**
         *  @todo do some processing for this announcement , specifically with the links
         */
    }

}

?>
