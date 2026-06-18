PAGE_SIZE = 16
page_table = {0: 5, 1: 2, 2: 1, 4: 7, 6: 0, 7: 4}  # pages 3 and 5 are invalid

addresses = [20, 100, 48, 16, 127, 91]  # N=91 for a=9, b=1

print("=" * 55)
print("Paging Address Translation  (page size = 16 bytes)")
print("=" * 55)
for LA in addresses:
    page   = LA // PAGE_SIZE
    offset = LA %  PAGE_SIZE
    if page in page_table:
        frame    = page_table[page]
        physical = frame * PAGE_SIZE + offset
        print(f"Logical {LA:>3} -> page {page}, offset {offset:>2} -> frame {frame} -> physical {physical}")
    else:
        print(f"Logical {LA:>3} -> page {page}, offset {offset:>2} -> Page fault: page not in memory")
