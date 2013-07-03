<?php

/* * *
 * Defines the Saic Page Issue class for migration processes.
 */

/**
 * The Page class is an extension of the Migration class,
 * representing distinct steps in a migration of the Page content type
 * process.  This will be Migration objects which actually import
 * data from a SAIC Drupal6 into a LEIDOS Drupal7  destination, 
 * By deriving classes directly from Migration class we will have other sorts of tasks 
 * of modules occur during the migration process.
 */
class saicPagesMigration extends Migration {

    // class constructor 
    public function __construct() {
        //parent constructor override 
        parent::__construct(MigrateGroup::getInstance('group3'));
        $this->description = t('Migrate Drupal6 SAIC page content type into LEIDOS D7');

        //source definition
        // field definitions; 
        $source_fields = array(
            'nid' => t('Node NID'),
        );

        // Import Page nodes from the saic D6
        $query = db_select(SOURCE_DATABASE . '.node', 'n')
                ->fields('n', array('nid', 'vid', 'type', 'language', 'title', 'uid', 'status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'))
                ->condition('n.type', 'page', '=');
        // Join the revisions associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.node_revisions', 'nr', 'n.vid = nr.vid');
        $query->addField('nr', 'body');
        $query->addField('nr', 'teaser');

        // Join the user associated with this announcement type node
        $query->join(SOURCE_DATABASE . '.users', 'u', 'n.uid = u.uid');
        $query->addField('u', 'name');

        // Join the data stored in the content type field associated with this announcement node(D6 table structure)
        $query->join(SOURCE_DATABASE . '.content_type_page', 'tp', 'n.nid = tp.nid');
        $query->addField('tp', 'field_page_image_fid');
        $query->addField('tp', 'field_page_image_list');
        $query->addField('tp', 'field_page_image_data');
        $query->addField('tp', 'field_page_teaser_value');


        $query->join(SOURCE_DATABASE . '.content_field_k', 'fk', 'n.vid = fk.vid');
        $query->addField('fk', 'field_page_breadcrumb_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_header_header_style', 'hhs', 'n.vid = hhs.vid');
        $query->addField('hhs', 'field_pod_header_header_style_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_header_subtitle', 'phs', 'n.vid = phs.vid');
        $query->addField('phs', 'field_pod_header_subtitle_value');

        $query->join(SOURCE_DATABASE . '.content_field_b', 'fb', 'n.vid = fb.vid');
        $query->addField('fb', 'field_b_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_list_group_description', 'fplgd', 'n.vid = fplgd.vid');
        $query->addField('fplgd', 'field_pod_list_group_description_value');

        $query->join(SOURCE_DATABASE . '.content_field_list_group_display', 'flgd', 'n.vid = flgd.vid');
        $query->addField('flgd', 'field_list_group_display_value');

        $query->join(SOURCE_DATABASE . '.content_field_list_group_description', 'flgd', 'n.vid = flgd.vid');
        $query->addField('flgd', 'field_list_group_description_value');

        $query->join(SOURCE_DATABASE . '.content_field_list_group_tags', 'flgd', 'n.vid = flgd.vid');
        $query->addField('flgd', 'field_list_group_tags_content_type');
        $query->addField('flgd', 'field_list_group_tags_private_tags');
        $query->addField('flgd', 'field_list_group_tags_public_tags');
        $query->addField('flgd', 'field_list_group_tags_tweet_tags');
        $query->addField('flgd', 'field_list_group_tags_content_limit');

        $query->join(SOURCE_DATABASE . '.content_field_list_group_heading_link', 'flhl', 'n.vid = flhl.vid');
        $query->addField('flhl', 'field_list_group_heading_link_url');
        $query->addField('flhl', 'field_list_group_heading_link_title');
        $query->addField('flhl', 'field_list_group_heading_link_attributes');

        $query->join(SOURCE_DATABASE . '.content_field_pod_list_group_display', 'plgd', 'n.vid = plgd.vid');
        $query->addField('plgd', 'field_pod_list_group_display_value');

        $query->join(SOURCE_DATABASE . '.content_field_list_group_tags_show_date', 'lgtsd', 'n.vid = lgtsd.vid');
        $query->addField('lgtsd', 'field_list_group_tags_show_date_value');

        $query->join(SOURCE_DATABASE . '.content_field_list_group_tags_m', 'flgtm', 'n.vid = flgtm.vid');
        $query->addField('flgtm', 'field_list_group_tags_m_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_l_n_i_list_group', 'fplnilg', 'n.vid = fplnilg.vid');
        $query->addField('fplnilg', 'field_pod_l_n_i_list_group_nid');

        $query->join(SOURCE_DATABASE . '.content_field_c', 'fc', 'n.vid = fc.vid');
        $query->addField('fc', 'field_c_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_list_open_item_desc', 'fploid', 'n.vid = fploid.vid');
        $query->addField('fploid', 'field_pod_list_open_item_desc_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_list_open_item_image', 'cfploii', 'n.vid = cfploii.vid');
        $query->addField('cfploii', 'field_pod_list_open_item_image_fid');
        $query->addField('cfploii', 'field_pod_list_open_item_image_list');
        $query->addField('cfploii', 'field_pod_list_open_item_image_data');

        $query->join(SOURCE_DATABASE . '.content_field_pod_list_open_item_url', 'loiu', 'n.vid = loiu.vid');
        $query->addField('loiu', 'field_pod_list_open_item_url_url');
        $query->addField('loiu', 'field_pod_list_open_item_url_title');
        $query->addField('loiu', 'field_pod_list_open_item_url_attributes');

        $query->join(SOURCE_DATABASE . '.content_field_pod_list_open_item_file', 'loif', 'n.vid = loif.vid');
        $query->addField('loif', 'field_pod_list_open_item_file_fid');
        $query->addField('loif', 'field_pod_list_open_item_file_list');
        $query->addField('loif', 'field_pod_list_open_item_file_data');

        $query->join(SOURCE_DATABASE . '.content_field_d', 'fd', 'n.vid = fd.vid');
        $query->addField('fd', 'field_d_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_spotlight_desc', 'psd', 'n.vid = psd.vid');
        $query->addField('psd', 'field_pod_spotlight_desc_value');
        $query->addField('psd', 'field_pod_spotlight_desc_format');

        $query->join(SOURCE_DATABASE . '.content_field_pod_spotlight_bg_image', 'fpsbi', 'n.vid = fpsbi.vid');
        $query->addField('fpsbi', 'field_pod_spotlight_bg_image_fid');
        $query->addField('fpsbi', 'field_pod_spotlight_bg_image_list');
        $query->addField('fpsbi', 'field_pod_spotlight_bg_image_data');

        $query->join(SOURCE_DATABASE . '.content_field_pod_spotlight_img_align', 'fpsia', 'n.vid = fpsia.vid');
        $query->addField('fpsia', 'field_pod_spotlight_img_align_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_gold_btn_text', 'pgbt', 'n.vid = pgbt.vid');
        $query->addField('pgbt', 'field_pod_gold_btn_text_value');
        $query->addField('pgbt', 'delta');

        $query->join(SOURCE_DATABASE . '.content_field_pod_gold_btn_action', 'pgba', 'n.vid = pgba.vid');
        $query->addField('pgba', 'field_pod_gold_btn_action_url');
        $query->addField('pgba', 'field_pod_gold_btn_action_title');
        $query->addField('pgba', 'field_pod_gold_btn_action_attributes');

        $query->join(SOURCE_DATABASE . '.content_field_pod_open_html_content', 'pohc', 'n.vid = pohc.vid');
        $query->addField('pohc', 'field_pod_open_html_content_value');
        $query->addField('pohc', 'field_pod_open_html_content_format');

        $query->join(SOURCE_DATABASE . '.content_field_page_openhtml_showborder', 'pos', 'n.vid = pos.vid');
        $query->addField('pos', 'field_page_openhtml_showborder_value');

        $query->join(SOURCE_DATABASE . '.content_field_page_openhtml_class_wrap', 'pocw', 'n.vid = pocw.vid');
        $query->addField('pocw', 'field_page_openhtml_class_wrap_value');

        $query->join(SOURCE_DATABASE . '.content_field_f', 'pocw', 'n.vid = pocw.vid');
        $query->addField('ff', 'field_f_value');

        $query->join(SOURCE_DATABASE . '.content_field_g', 'cfg', 'n.vid = cfg.vid');
        $query->addField('cfg', 'field_g_value');

        $query->join(SOURCE_DATABASE . '.content_field_h', 'cfh', 'n.vid = cfh.vid');
        $query->addField('cfg', 'field_h_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_faq_item_answer', 'pfia', 'n.vid = pfia.vid');
        $query->addField('pfia', 'field_pod_faq_item_answer_value');
        $query->addField('pfia', 'field_pod_faq_item_answer_format');

        $query->join(SOURCE_DATABASE . '.content_field_pod_content_top_image', 'fpcti', 'n.vid = fpcti.vid');
        $query->addField('fpcti', 'field_pod_content_top_image_fid');
        $query->addField('fpcti', 'field_pod_content_top_image_list');
        $query->addField('fpcti', 'field_pod_content_top_image_data');

        $query->join(SOURCE_DATABASE . '.content_field_content_top_image_link', 'cfctil', 'n.vid = cfctil.vid');
        $query->addField('cfctil', 'field_content_top_image_link_url');
        $query->addField('cfctil', 'field_content_top_image_link_title');
        $query->addField('cfctil', 'field_content_top_image_link_attributes');

        $query->join(SOURCE_DATABASE . '.content_field_pod_content_top_text', 'cfpctt', 'n.vid = cfpctt.vid');
        $query->addField('cfpctt', 'field_pod_content_top_text_value');
        $query->addField('cfpctt', 'field_pod_content_top_text_format');

        $query->join(SOURCE_DATABASE . '.content_field_content_top_t_i_link', 'cfcttil', 'n.vid = cfcttil.vid');
        $query->addField('cfcttil', 'field_content_top_t_i_link_url');
        $query->addField('cfcttil', 'field_content_top_t_i_link_title');
        $query->addField('cfcttil', 'field_content_top_t_i_link_attributes');

        $query->join(SOURCE_DATABASE . '.content_field_content_top_t_i_line', 'cfcttiln', 'n.vid = cfcttiln.vid');
        $query->addField('cfcttiln', 'field_content_top_t_i_line_value');

        $query->join(SOURCE_DATABASE . '.content_field_content_top_t_i_border', 'cfcttibr', 'n.vid = cfcttibr.vid');
        $query->addField('cfcttibr', 'field_content_top_t_i_border_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_ft_i_b_sn_image', 'cfpftibsni', 'n.vid = cfpftibsni.vid');
        $query->addField('cfpftibsni', 'field_pod_ft_i_b_sn_image_fid');
        $query->addField('cfpftibsni', 'field_pod_ft_i_b_sn_image_list');
        $query->addField('cfpftibsni', 'field_pod_ft_i_b_sn_image_data');

        $query->join(SOURCE_DATABASE . '.content_field_pod_ft_i_b_sn_button', 'cfpftibsnb', 'n.vid = cfpftibsnb.vid');
        $query->addField('cfpftibsnb', 'field_pod_ft_i_b_sn_button_url');
        $query->addField('cfpftibsnb', 'field_pod_ft_i_b_sn_button_title');
        $query->addField('cfpftibsnb', 'field_pod_ft_i_b_sn_button_attributes');

        $query->join(SOURCE_DATABASE . '.content_field_pod_ft_i_b_sn_rotator', 'bsnrot', 'n.vid = bsnrot.vid');
        $query->addField('bsnrot', 'field_pod_ft_i_b_sn_rotator_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_ft_i_b_sn_move_nav', 'bsnmvnav', 'n.vid = bsnmvnav.vid');
        $query->addField('bsnmvnav', 'field_pod_ft_i_b_sn_move_nav_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_ft_i_b_sn_nav_tag', 'pdftibsnnvtg', 'n.vid = pdftibsnnvtg.vid');
        $query->addField('pdftibsnnvtg', 'field_pod_ft_i_b_sn_nav_tag_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_callout_desc', 'pcds', 'n.vid = pcds.vid');
        $query->addField('pcds', 'field_pod_callout_desc_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_callout_image', 'cfldpdcoutim', 'n.vid = cfldpdcoutim.vid');
        $query->addField('cfldpdcoutim', 'field_pod_callout_image_fid');
        $query->addField('cfldpdcoutim', 'field_pod_callout_image_list');
        $query->addField('cfldpdcoutim', 'field_pod_callout_image_data');

        $query->join(SOURCE_DATABASE . '.content_field_pod_callout_link', 'fpcotlk', 'n.vid = fpcotlk.vid');
        $query->addField('fpcotlk', 'field_pod_callout_link_url');
        $query->addField('fpcotlk', 'field_pod_callout_link_title');
        $query->addField('fpcotlk', 'field_pod_callout_link_attributes');

        $query->join(SOURCE_DATABASE . '.content_field_pod_callout_link_target', 'cfpdclllntgt', 'n.vid = cfpdclllntgt.vid');
        $query->addField('cfpdclllntgt', 'field_pod_callout_link_target_value');

        $query->join(SOURCE_DATABASE . '.content_field_block_openhtml_class_wrap', 'cfbopnclwr', 'n.vid = cfbopnclwr.vid');
        $query->addField('cfbopnclwr', 'field_block_openhtml_class_wrap_value');

        $query->join(SOURCE_DATABASE . '.content_field_pod_block_ref', 'cfpdblref', 'n.vid = cfpdblref.vid');
        $query->addField('cfpdblref', 'field_pod_block_ref_value');
        $query->addField('cfpdblref', 'field_pod_block_ref_format');

        $query->join(SOURCE_DATABASE . '.content_field_pod_block_showborder', 'cfpodblshw', 'n.vid = cfpodblshw.vid');
        $query->addField('cfpodblshw', 'field_pod_block_showborder_value');

        $query->join(SOURCE_DATABASE . '.content_field_j', 'cfj', 'n.vid = cfj.vid');
        $query->addField('cfj', 'field_j_value');

        $query->join(SOURCE_DATABASE . '.content_field_i', 'cfi', 'n.vid = cfi.vid');
        $query->addField('cfi', 'field_i_value');

        $query->join(SOURCE_DATABASE . '.content_field_page_layout', 'cfply', 'n.vid = cfply.vid');
        $query->addField('cfply', 'field_page_layout_value');

        $query->join(SOURCE_DATABASE . '.content_field_page_left_menu', 'cfplftmn', 'n.vid = cfplftmn.vid');
        $query->addField('cfplftmn', 'field_page_left_menu_value');

        $query->join(SOURCE_DATABASE . '.content_field_page_breadcrumb', 'cfldpbr', 'n.vid = cfldpbr.vid');
        $query->addField('cfldpbr', 'field_page_breadcrumb_value');

        $query->join(SOURCE_DATABASE . '.content_field_disclaimer', 'cfdiscl', 'n.vid = cfdiscl.vid');
        $query->addField('cfdiscl', 'field_disclaimer_nid');

        $query->join(SOURCE_DATABASE . '.content_field_parent_menu', 'cfprmn', 'n.vid = cfprmn.vid');
        $query->addField('cfprmn', 'field_parent_menu_value');





        $query->orderBy('n.nid', 'ASC');

        $this->source = new MigrateSourceSQL($query, $source_fields);

        //destination definition
        $this->destination = new MigrateDestinationNode('page');

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
        $this->addFieldMapping('field_page_image', 'field_page_image_fid');
        $this->addFieldMapping('field_page_teaser', 'field_page_teaser_value');
        $this->addFieldMapping('field_k', 'field_k_value');
        $this->addFieldMapping('field_pod_header_header_style', 'field_pod_header_header_style_value');
        $this->addFieldMapping('field_pod_header_subtitle', 'field_pod_header_subtitle_value');
        $this->addFieldMapping('field_b', 'field_b_value');
        $this->addFieldMapping('field_pod_list_group_description', 'field_pod_list_group_description_value');
        $this->addFieldMapping('field_pod_list_group_display', 'field_list_group_display_value');
        $this->addFieldMapping('field_list_group_description', 'field_list_group_description_value');
        $this->addFieldMapping('field_list_group_tags', 'field_list_group_tags_content_type');
        $this->addFieldMapping('field_list_group_heading_link', 'field_list_group_heading_link_url');
        $this->addFieldMapping('field_list_group_display', 'field_pod_list_group_display_value');
        $this->addFieldMapping('field_list_group_tags_show_date', 'field_list_group_tags_show_date_value');
        $this->addFieldMapping('field_list_group_tags_m', 'field_list_group_tags_m_value');
        $this->addFieldMapping('field_pod_l_n_i_list_group', 'field_pod_l_n_i_list_group_nid');
        $this->addFieldMapping('field_c', 'field_c_value');
        $this->addFieldMapping('field_pod_list_open_item_desc', 'field_pod_list_open_item_desc_value');
        $this->addFieldMapping('field_pod_list_open_item_image', 'field_pod_list_open_item_image_fid');
        $this->addFieldMapping('field_pod_list_open_item_url', 'field_pod_list_open_item_url_url');
        $this->addFieldMapping('field_pod_list_open_item_url:title', 'field_pod_list_open_item_url_title');
        $this->addFieldMapping('field_pod_list_open_item_url:attributes', 'field_pod_list_open_item_url_attributes');
        $this->addFieldMapping('field_pod_list_open_item_file', 'field_pod_list_open_item_file_fid');
        $this->addFieldMapping('field_pod_list_open_item_file:list', 'field_pod_list_open_item_file_list');
        $this->addFieldMapping('field_pod_list_open_item_file:data', 'field_pod_list_open_item_file_data');
        $this->addFieldMapping('field_d', 'field_d_value');
        $this->addFieldMapping('field_pod_spotlight_desc', 'field_pod_spotlight_desc_value');
        $this->addFieldMapping('field_pod_spotlight_desc:format', 'field_pod_spotlight_desc_format');
        $this->addFieldMapping('field_pod_spotlight_bg_image', 'field_pod_spotlight_bg_image_fid');
        $this->addFieldMapping('field_pod_spotlight_bg_image:list', 'field_pod_spotlight_bg_image_list');
        $this->addFieldMapping('field_pod_spotlight_bg_image:data', 'field_pod_spotlight_bg_image_data');
        $this->addFieldMapping('field_pod_spotlight_img_align', 'field_pod_spotlight_img_align_value');
        $this->addFieldMapping('field_pod_spotlight_file', 'field_pod_spotlight_file_fid');
        $this->addFieldMapping('field_pod_spotlight_file:list', 'field_pod_spotlight_file_list');
        $this->addFieldMapping('field_pod_spotlight_file:data', 'field_pod_spotlight_file_data');
        $this->addFieldMapping('field_pod_gold_btn_fields', 'field_pod_gold_btn_fields_value');
        $this->addFieldMapping('field_pod_gold_btn_fields:format', 'field_pod_gold_btn_fields_format');
        $this->addFieldMapping('field_pod_gold_btn_text', 'field_pod_gold_btn_text_value');
        $this->addFieldMapping('field_pod_gold_btn_text:delta', 'delta');
        $this->addFieldMapping('field_pod_gold_btn_action', 'field_pod_gold_btn_action_url');
        $this->addFieldMapping('field_pod_gold_btn_action:title', 'field_pod_gold_btn_action_title');
        $this->addFieldMapping('field_pod_gold_btn_action:attributes', 'field_pod_gold_btn_action_attributes');
        $this->addFieldMapping('field_pod_open_html_content', 'field_pod_open_html_content_value');
        $this->addFieldMapping('field_pod_open_html_content:format', 'field_pod_open_html_content_format');
        $this->addFieldMapping('field_page_openhtml_showborder', 'field_page_openhtml_showborder_value');
        $this->addFieldMapping('field_page_openhtml_class_wrap', 'field_page_openhtml_class_wrap_value');
        $this->addFieldMapping('field_f', 'field_f_value');
        $this->addFieldMapping('field_g', 'field_g_value');
        $this->addFieldMapping('field_h', 'field_h_value');
        $this->addFieldMapping('field_pod_faq_item_answer', 'field_pod_faq_item_answer_value');
        $this->addFieldMapping('field_pod_faq_item_answer:format', 'field_pod_faq_item_answer_format');
        $this->addFieldMapping('field_pod_content_top_image', 'field_pod_content_top_image_fid');
        $this->addFieldMapping('field_pod_content_top_image:list', 'field_pod_content_top_image_list');
        $this->addFieldMapping('field_pod_content_top_image:data', 'field_pod_content_top_image_data');
        $this->addFieldMapping('field_content_top_image_link', 'field_content_top_image_link_url');
        $this->addFieldMapping('field_content_top_image_link:title', 'field_content_top_image_link_title');
        $this->addFieldMapping('field_content_top_image_link:attributes', 'field_content_top_image_link_attributes');
        $this->addFieldMapping('field_pod_content_top_text', 'field_pod_content_top_text_value');
        $this->addFieldMapping('field_pod_content_top_text:format', 'field_pod_content_top_text_format');
        $this->addFieldMapping('field_pod_content_top_img', 'field_pod_content_top_img_fid');
        $this->addFieldMapping('field_pod_content_top_img:list', 'field_pod_content_top_img_list');
        $this->addFieldMapping('field_pod_content_top_img:data', 'field_pod_content_top_img_data');
        $this->addFieldMapping('field_content_top_t_i_link', 'field_content_top_t_i_link_url');
        $this->addFieldMapping('field_content_top_t_i_link:title', 'field_content_top_t_i_link_title');
        $this->addFieldMapping('field_content_top_t_i_link:attributes', 'field_content_top_t_i_link_attributes');
        $this->addFieldMapping('field_content_top_t_i_line', 'field_content_top_t_i_line_value');
        $this->addFieldMapping('field_content_top_t_i_border', 'field_content_top_t_i_border_value');
        $this->addFieldMapping('field_pod_ft_i_b_sn_image', 'field_pod_ft_i_b_sn_image_fid');
        $this->addFieldMapping('field_pod_ft_i_b_sn_image:list', 'field_pod_ft_i_b_sn_image_list');
        $this->addFieldMapping('field_pod_ft_i_b_sn_image:data', 'field_pod_ft_i_b_sn_image_data');
        $this->addFieldMapping('field_pod_ft_i_b_sn_button', 'field_pod_ft_i_b_sn_button_url');
        $this->addFieldMapping('field_pod_ft_i_b_sn_button:title', 'field_pod_ft_i_b_sn_button_title');
        $this->addFieldMapping('field_pod_ft_i_b_sn_button:attributes', 'field_pod_ft_i_b_sn_button_attributes');
        $this->addFieldMapping('field_pod_ft_i_b_sn_rotator', 'field_pod_ft_i_b_sn_rotator_value');
        $this->addFieldMapping('field_pod_ft_i_b_sn_move_nav', 'field_pod_ft_i_b_sn_move_nav_value');
        $this->addFieldMapping('field_pod_ft_i_b_sn_nav_tag', 'field_pod_ft_i_b_sn_nav_tag_value');
        $this->addFieldMapping('field_pod_callout_desc', 'field_pod_callout_desc_value');
        $this->addFieldMapping('field_pod_callout_image', 'field_pod_callout_image_fid');
        $this->addFieldMapping('field_pod_callout_image:list', 'field_pod_callout_image_list');
        $this->addFieldMapping('field_pod_callout_image:data', 'field_pod_callout_image_data');
        $this->addFieldMapping('field_pod_callout_link', 'field_pod_callout_link_url');
        $this->addFieldMapping('field_pod_callout_link:title', 'field_pod_callout_link_title');
        $this->addFieldMapping('field_pod_callout_link:attributes', 'field_pod_callout_link_attributes');
        $this->addFieldMapping('field_pod_callout_link_target', 'field_pod_callout_link_target_value');
        $this->addFieldMapping('field_block_openhtml_class_wrap', 'field_block_openhtml_class_wrap_value');
        $this->addFieldMapping('field_pod_block_ref', 'field_pod_block_ref_value');
        $this->addFieldMapping('field_pod_block_ref:format', 'ffield_pod_block_ref_format');
        $this->addFieldMapping('field_pod_block_showborder', 'field_pod_block_showborder_value');
        $this->addFieldMapping('field_j', 'field_j_value');
        $this->addFieldMapping('field_i', 'field_i_value');
        $this->addFieldMapping('field_page_layout', 'field_page_layout_value');
        $this->addFieldMapping('field_page_left_menu', 'field_page_left_menu_value');
        $this->addFieldMapping('field_page_breadcrumb', 'field_page_breadcrumb_value');
        $this->addFieldMapping('field_disclaimer', 'field_disclaimer_nid');
        $this->addFieldMapping('field_parent_menu', 'field_parent_menu_value');

        //here we have anmapped fields
    }

    public function prepareRow($current_row) {
        /**
         *  @todo do some processing for this announcement , specifically with the links, thumbnail
         */
    }

}

?>
