<?php
// $Id: block.tpl.php,v 1.1 2009/12/25 18:00:00 mosatron Exp $
?>				
			
<!-- start block.tpl.php -->
			
<div class="block-wrapper <?php print $block_zebra; ?>">

	<div class="block-top"></div>
	
	<div class="block clearfix">
	
		<h2 class="title"><img src="<?php global $base_path; print $base_path.path_to_theme(); ?>/images/titles/search_pn_block.png" alt="Search PovNet" /></h2>
		
		<div class="content clearfix">
		    <?php print $block->content; ?>
			
			<a href="/search"><img src="<?php global $base_path; print $base_path.path_to_theme(); ?>/images/icons/search_50px.png" alt="Search Icon" class="icon" /></a>
			<p class="more"><a href="/search">Advanced search</a> options</p>		
			<p class="more">Browse <a href="/site-map">site map</a></p>
		</div>

	  <?php print $edit_links; ?>		
		
	</div>
	
<div class="block-btm"></div>

</div> <!-- end block-wrapper -->

<!-- /end block.tpl.php -->