<?php

// User Migration class
class saicContractsMigration extends Migration {

    // class constructor
    public function __construct() {
        parent::__construct(MigrateGroup::getInstance('group3'));
        $this->description = t('Migrate Drupal 6 contracts types to D7');

        //... SOURCE
        // some field definitions; roles will be added later in prepareRow()
        $source_fields = array(
            'nid' => t('Node NID'),
            'metatags' => t('metatags data'),
        );

        // Import nodes from the old db
        $query = db_select(SOURCE_DATABASE . '.node', 'n')
                ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
                ->condition('n.type', 'contract', '=');

        $query->join(SOURCE_DATABASE . '.node_revisions', 'nr', 'n.vid = nr.vid');
        $query->addField('nr', 'body');
        $query->addField('nr', 'teaser');

        $query->join(SOURCE_DATABASE . '.users', 'u', 'n.uid = u.uid');
        $query->addField('u', 'name');

        $query->join(SOURCE_DATABASE . '.content_type_contract', 'cc', 'n.nid = cc.nid');
        $query->addField('cc', 'field_contract_acronym_value');
        $query->addField('cc', 'field_contract_contact_info_value');
        $query->addField('cc', 'field_contract_number_value');
        $query->addField('cc', 'field_contract_teaser_value');

        $query->join(SOURCE_DATABASE . '.content_field_page_breadcrumb', 'pb', 'n.vid = pb.vid');
        $query->addField('pb', 'field_page_breadcrumb_value');

        $query->join(SOURCE_DATABASE . '.content_field_page_left_menu', 'lm', 'n.vid = lm.vid');
        $query->addField('lm', 'field_page_left_menu_value');




        $query->orderBy('n.nid', 'ASC');

        $this->source = new MigrateSourceSQL($query, $source_fields);
        //....
        //DESTINATION
        $this->destination = new MigrateDestinationNode('contract');

        //...
        // ... MAPPING
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
        // ...
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

        // These can be individually mapped as we see here.
        $this->addFieldMapping('body', 'body');
        //$this->addFieldMapping('teaser', 'teaser');
        $this->addFieldMapping('body:summary', 'teaser');



        $this->addFieldMapping('field_contract_acronym', 'field_contract_acronym_value');
        $this->addFieldMapping('field_contract_contact_info', 'field_contract_contact_info_value');
        $this->addFieldMapping('field_contract_number', 'field_contract_number_value');
        $this->addFieldMapping('field_contract_teaser', 'field_contract_teaser_value');

        $this->addFieldMapping('field_page_breadcrumb', 'field_page_breadcrumb_value');
        $this->addFieldMapping('field_page_left_menu', 'field_page_left_menu_value');






        // Unmapped destination fields
        //$this->addUnmigratedDestinations(array('field_address'));
        // ...
    }

    public function prepareRow($current_row) {

//        //collects the nodeword data
//        $query = db_select(SOURCE_DATABASE . '.nodewords', 'nw')
//                ->fields('nw', array('mtid', 'type', 'id', 'name', 'content'))
//                ->condition('nw.id', $current_row->nid, '=');
//        $result = $query->execute();
//
//        //collect and place nodeword data in array for metatag data
//        foreach ($result as $row) {
//            $nodewords_data[$row->id]['entity_type'] = $row->type;
//            $nodewords_data[$row->id]['data'][$row->name]['value'] = trim(strip_tags($row->content));
//        }
//        $metatags = array();
//        //merg the nodeword data into the metatag data
//        foreach ($nodewords_data as $entity_id => $metatag_data) {
//            $id = (int) $entity_id;
//            $metatags['key'] = array('entity_type' => $metatag_data['entity_type'],'entity_id' => $id,);
//            $metatags['fields'] = array('data' => serialize($metatag_data['data']),);
//        }
//        $current_row->metatags = $metatags;
//        return TRUE;
    }

}

// close the ourContractsMigration class
?>
