select
  n.nid
  , n.type
--  , field_node_ref_nid as ref1
--  , n1.type as ref1_type
--  , field_node_ref2_nid as ref2
--  , n2.type as ref2_type
  , field_node_ref3_nid as ref3
  , n3.type as ref3_type
from
  node n
--  inner join content_field_node_ref cfnr1 on n.vid=cfnr1.vid and field_node_ref_nid is not null
--  inner join node n1 on n1.nid=cfnr1.field_node_ref_nid
--  inner join content_field_node_ref2 cfnr2 on n.vid=cfnr2.vid and field_node_ref2_nid is not null
--  inner join node n2 on n2.nid=cfnr2.field_node_ref2_nid
  inner join content_field_node_ref3 cfnr3 on n.vid=cfnr3.vid and field_node_ref3_nid is not null
  inner join node n3 on n3.nid=cfnr3.field_node_ref3_nid
order by
  n.type
  , ref3_type
;
