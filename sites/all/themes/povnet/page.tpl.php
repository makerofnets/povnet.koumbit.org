<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_classes; ?>">

	<div id="page-wrapper" class="clearfix">
		
		<div id="page" class="clearfix">
		
		
			<div id="top-nav">
			
			  <ul>
			  	<li class="home"><a href="<?php print $base_path ?>" title="<?php print t('Home'); ?>">Home</a></li>
			  	<li class="about"><a href="/about-us" title="About Us">About Us</a></li>
			  	<li class="help"><a href="/help" title="Help">Help</a></li>
			  	<li class="contact"><a href="/contact" title="Contact Us">Contact Us</a></li>
			  </ul>
			  
			</div> <!-- end top-nav -->

			
			<div id="header" class="clearfix">
				
				<?php if ($site_name): ?>
					<h1><?php print $site_name; ?></h1>
				<?php endif; ?>
				
				<?php if ($site_slogan): ?>
					<div class="slogan"><a href="<?php print $base_path ?>" title="<?php print t('Home'); ?>"><?php print $site_slogan; ?></a></div>
				<?php endif; ?>
				
				<div class="homedate">
					<?php print format_date(time(), 'custom', 'l F jS Y'); ?>
				</div>
				
				<div class="socmed">
					<a href="http://facebook.com/povnet"><img src="<?php global $base_path; print $base_path.path_to_theme(); ?>/images/misc/facebook_icon_20px.png" alt="PovNet on Facebook" longdesc="http://facebook.com" /></a>
					<a href="http://twitter.com/povnet"><img src="<?php global $base_path; print $base_path.path_to_theme(); ?>/images/misc/twitter_icon_20px.png" alt="PovNet on Twitter" longdesc="http://twitter.com" /></a>
					<a href="http://www.povnet.org/rss.xml"><img src="<?php global $base_path; print $base_path.path_to_theme(); ?>/images/misc/rss_icon_20px.png" alt="PovNet's RSS Feed" longdesc="http://povnet.org/feed.rss" /></a>
				</div> <!-- end socmed -->	

			</div> <!-- end header -->	


			<div id="three-col-layout" class="clearfix">			
			        
		        <?php if ($three_col_first): ?>
				<div class="column-first clearfix">
					<?php print $three_col_first; ?>
				</div> <!-- end column-first -->
		        <?php endif; ?>
				
				
				<div class="column-middle clearfix">

				    <?php if ($content_top): ?>
				    <div class="content-top clearfix">
				        <?php print $content_top; ?>
					</div> <!-- end content-top -->
				    <?php endif; ?>
					
					<div id="page-content" class="clearfix">
						
						<div class="txtsize"><a href="/help/text-size">Need to increase text size?</a></div>								
						
						<?php if ($tabs): ?>
						<div id="content-tabs">
							<?php print $tabs; ?>
						</div>
						<?php endif; ?>			

						<?php print $messages; ?>						
						
						<?php if ($title): ?>
						<h1 class="title"><?php print $title; ?></h1>
						<?php endif; ?>
						
						<?php print $help; ?>	
						
					    <div class="content">
							<?php print $content; ?>
						</div> <!-- end content -->
						
						<?php if ($feed_icons): ?>
						<div class="feed-icons"><?php print $feed_icons; ?></div>
						<?php endif; ?>
						
					</div> <!-- end page-content -->
					
				</div> <!-- end column-middle -->
				
				
				<div class="column-last clearfix">
					
		            <?php if ($three_col_last_top): ?>
		            <div class="column-last-top clearfix">
		              <?php print $three_col_last_top; ?>
					</div><!-- end column-last-top -->
		            <?php endif; ?>

		            <?php if ($three_col_sidebar_first): ?>
		            <div class="sidebar-first clearfix">
						<div class="sidebar-top"></div>
						<div class="sidebar clearfix">
							<?php print $three_col_sidebar_first; ?>
						</div>
						<div class="sidebar-btm"></div>
					</div> <!-- end sidebar-first -->	
		            <?php endif; ?>

		            <div class="sidebar-last clearfix">
						
						<!-- start permanent Google CSE search block -->
									
						<div class="block-wrapper-custom-search">

							<div class="block-top"></div>
							
							<div class="block clearfix">
							
								<h2 class="title"><img src="<?php global $base_path; print $base_path.path_to_theme(); ?>/images/titles/search_pn_block.png" alt="Search PovNet" /></h2>
								
								<div class="content clearfix">
								    <?php print drupal_get_form('google_cse_searchbox_form');?>
									
									<a href="/search"><img src="<?php global $base_path; print $base_path.path_to_theme(); ?>/images/icons/search_30px.png" alt="Search Icon" class="icon" /></a>
									<p class="more"><a href="/search">Advanced search</a></p>		
									<p class="more"><a href="/site-map">Site map</a></p>
								</div>

							  <?php print $edit_links; ?>		
								
							</div>
							
						<div class="block-btm"></div>

						</div> <!-- end block-wrapper -->

						<!-- /end permanent Google CSE search block -->
					
		              <?php print $three_col_sidebar_last; ?>
					</div> <!-- end sidebar-last -->					

					
				</div> <!-- end column-last -->
				
					
			</div> <!-- end three-col-layout -->
		
		
		
		</div> <!-- end page -->
			
		
		<div id="footer-wrapper">
		
			<div id="footer" class="clearfix">
			
				<?php if ($footer): ?>
				  <?php print $footer; ?>
				<?php endif; ?>			
			
		        <?php if ($footer_message): ?>
				<div class="colophon">
					<?php print $footer_message; ?>
				</div> <!-- end colophon -->
		        <?php endif; ?>
			
			</div> <!-- end footer -->
			
			<div class="footer-stripes"></div>
		
		</div> <!-- end footer-wrapper -->

	</div> <!-- end page-wrapper -->

	<?php print $closure ?>	

	</body>

</html>