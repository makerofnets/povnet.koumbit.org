<?php
// $Id: block.tpl.php,v 1.1 2009/12/25 18:00:00 mosatron Exp $
?>				
			
<!-- start block.tpl.php -->
			
<div class="block-wrapper <?php print $block_zebra; ?>">

	<div class="block-top"></div>
	
	<div class="block clearfix">
	
		<?php if ($block->subject): ?>
		<h2 class="title"><?php print $block->subject; ?></h2>
		<?php endif; ?>
		
		<div class="content clearfix">
		    <?php print $block->content; ?>
		</div>

	  <?php print $edit_links; ?>		
		
	</div>
	
<div class="block-btm"></div>

</div> <!-- end block-wrapper -->

<!-- /end block.tpl.php -->