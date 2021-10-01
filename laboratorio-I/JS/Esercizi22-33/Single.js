function single(a) {
    let s = 0;
    let e = a.length - 1;
    let tmpMid;
    while (s <= e) {
        mid = Math.floor((s + e) / 2)
        tmpMid = mid;

        if (a[mid] != a[mid + 1])
            tmpMid--;
        if (a[tmpMid] == a[tmpMid + 1]) {
            if (tmpMid%2 == 0 && (tmpMid + 1)%2 != 0)
                s = mid + 1
            else
                e = mid - 1
        } else
            return a[mid]
    }
}