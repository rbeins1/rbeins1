<?php

/* * *
 * Defines the Saic Magazine Issue class for migration processes.
 */

/**
 * The Magazine Issue class is an extension of the Migration class,
 * representing distinct steps in a migration of the magazines Issue content type
 * process.  This will be Migration objects which actually import
 * data from a SAIC Drupal6 into a LEIDOS Drupal7  destination, 
 * By deriving classes directly from Migration class we will have other sorts of tasks 
 * of modules occur during the migration process.
 */
class saicMagazineIssuesMigration extends Migration {

    // class constructor 
    public function __construct() {
        //parent constructor override 
        parent::__construct(MigrateGroup::getInstance('group3'));
        $this->description = t('Migrate Drupal6 SAIC magazine Issue content type into LEIDOS D7');

        //source definition
        // field definitions; 
        $source_fields = array(
            'nid' => t('Node NID'),
        );

        // Import Magazine Issue nodes from the saic D6
        $query = db_select(SOURCE_DATABASE . '.node', 'n')
                ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
                ->condition('n.type', 'magazine_issue', '=');
        // Join the revisions associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.node_revisions', 'nr', 'n.vid = nr.vid');
        $query->addField('nr', 'body');
        $query->addField('nr', 'teaser');

        // Join the user associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.users', 'u', 'n.uid = u.uid');
        $query->addField('u', 'name');

        // Join the data stored in the content type field associated with this announcement node(D6 table structure)
        $query->join(SOURCE_DATABASE . '.content_type_magazine_issue', 'mi', 'n.nid = mi.nid');
        $query->addField('mi', 'field_magazine_issue_magazine_nid');
        $query->addField('mi', 'field_magazine_issue_date_title_value');
        $query->addField('mi', 'field_magazine_issue_archive_value');
        $query->addField('mi', 'field_magazine_issue_image_fid');
        $query->addField('mi', 'field_magazine_issue_image_list');
        $query->addField('mi', 'field_magazine_issue_image_data');
        $query->addField('mi', 'field_magazine_issue_pdf_fid');
        $query->addField('mi', 'field_magazine_issue_pdf_list');
        $query->addField('mi', 'field_magazine_issue_pdf_data');
        $query->addField('mi', 'field_magazine_issue_side_image_fid');
        $query->addField('mi', 'field_magazine_issue_side_image_list');
        $query->addField('mi', 'field_magazine_issue_side_image_data');




        $query->join(SOURCE_DATABASE . '.content_field_magazine_custom_title', 'ct', 'n.vid = ct.vid');
        $query->addField('ct', 'field_page_breadcrumb_value');

        $query->join(SOURCE_DATABASE . '.content_field_magazine_custom_content', 'cc', 'n.vid = cc.vid');
        $query->addField('cc', 'field_magazine_custom_content_value');


        $query->orderBy('n.nid', 'ASC');

        $this->source = new MigrateSourceSQL($query, $source_fields);

        //destination definition
        $this->destination = new MigrateDestinationNode('magazine_issue');

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


        // Custom field mappping 
        $this->addFieldMapping('field_magazine_issue_magazine', 'field_magazine_issue_magazine_nid');
        $this->addFieldMapping('field_magazine_issue_date_title', 'field_magazine_issue_date_title_value');
        $this->addFieldMapping('field_magazine_issue_archive', 'field_magazine_issue_archive_value');
        $this->addFieldMapping('field_magazine_issue_image', 'field_magazine_issue_image_fid');
        $this->addFieldMapping('field_magazine_issue_pdf', 'field_magazine_issue_pdf_fid');
        $this->addFieldMapping('field_magazine_issue_side_image', 'field_magazine_issue_side_image_fid');

        //here we have anmapped fields
    }

    public function prepareRow($current_row) {
        /**
         *  @todo do some processing for this announcement , specifically with the links, thumbnail
         */
    }

}

?>
