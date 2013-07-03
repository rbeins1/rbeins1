<?php

/* * *
 * Defines the Saic Magazine Article class for migration processes.
 */

/**
 * The Magazine Article class is an extension of the Migration class,
 * representing distinct steps in a migration of the magazines article content type
 * process.  This will be Migration objects which actually import
 * data from a SAIC Drupal6 into a LEIDOS Drupal7  destination, 
 * By deriving classes directly from Migration class we will have other sorts of tasks 
 * of modules occur during the migration process.
 */
class saicMagazineArticlesMigration extends Migration {

    // class constructor 
    public function __construct() {
        //parent constructor override 
        parent::__construct(MigrateGroup::getInstance('group3'));
        $this->description = t('Migrate Drupal6 SAIC magazine article content type into LEIDOS D7');

        //source definition
        // field definitions; 
        $source_fields = array(
            'nid' => t('Node NID'),
        );

        // Import announcement nodes from the saic D6
        $query = db_select(SOURCE_DATABASE . '.node', 'n')
                ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
                ->condition('n.type', 'magazine_article', '=');
        // Join the revisions associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.node_revisions', 'nr', 'n.vid = nr.vid');
        $query->addField('nr', 'body');
        $query->addField('nr', 'teaser');

        // Join the user associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.users', 'u', 'n.uid = u.uid');
        $query->addField('u', 'name');

        // Join the data stored in the content type field associated with this announcement node(D6 table structure)
        $query->join(SOURCE_DATABASE . '.content_type_magazine_article', 'ma', 'n.nid = ma.nid');
        $query->addField('ma', 'field_magazine_article_issue_nid');
        $query->addField('ma', 'field_magazine_article_teaser_value');
        $query->addField('ma', 'field_magazine_article_image_fid');
        $query->addField('ma', 'field_magazine_article_image_list');
        $query->addField('ma', 'field_magazine_article_image_data');


        $query->join(SOURCE_DATABASE . '.content_field_magazine_custom_title', 'ct', 'n.vid = ct.vid');
        $query->addField('ct', 'field_page_breadcrumb_value');

        $query->join(SOURCE_DATABASE . '.content_field_magazine_custom_content', 'cc', 'n.vid = cc.vid');
        $query->addField('cc', 'field_magazine_custom_content_value');


        $query->orderBy('n.nid', 'ASC');

        $this->source = new MigrateSourceSQL($query, $source_fields);

        //destination definition
        $this->destination = new MigrateDestinationNode('magazine_article');

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
        $this->addFieldMapping('field_magazine_article_issue', 'field_magazine_article_issue_nid');
        $this->addFieldMapping('field_magazine_article_teaser', 'field_magazine_article_teaser_value');
        $this->addFieldMapping('field_magazine_article_image', 'field_magazine_article_image_fid');
        $this->addFieldMapping('field_magazine_custom_title', 'field_magazine_custom_title_value');
        $this->addFieldMapping('field_magazine_custom_content', 'field_magazine_custom_content_value');

        //here we have anmapped fields
    }

    public function prepareRow($current_row) {
        /**
         *  @todo do some processing for this announcement , specifically with the links, thumbnail
         */
    }

}

?>
