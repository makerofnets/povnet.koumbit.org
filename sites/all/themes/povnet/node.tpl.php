<?php 
// $Id: node.tpl.php,v 1.1 2009/12/25 18:00:00 mosatron Exp $
?>

<!-- start node.tpl.php -->

<div id="node-<?php print $node->nid; ?>" class="node <?php print $node_classes; ?>">

  <?php print $picture ?>

  <?php if (!$page): ?>
  <h2 class="title"><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
  <?php endif; ?>

  <div class="meta">
    <?php if ($submitted): ?>
    <span class="submitted">Posted on: <?php print $date ?></span>
    <?php endif; ?>
  </div>

  <div class="node-content">
    <?php print $content ?>
  </div>

  <?php if ($terms): ?>
  <div class="terms">
    <strong>Keywords: </strong><?php print $terms; ?>
  </div>
  <?php endif;?>
  
  <?php if ($links): ?>
  <div class="links">
    <?php print $links; ?>
  </div>
  <?php endif; ?>

</div>
<!-- end node-<?php print $node->nid; ?> -->