#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
index = ['sales', 'returns', 'credit fees',
         'rebates', 'late charges', 'shipping']
data={'amount': [350000, -30000, -7500, -25000, 95000, -7000]}
trans=pd.DataFrame(data=data, index=index)
blank = trans.amount.cumsum().shift(1).fillna(0)
total = trans.sum().amount
trans.loc["net"] = total
blank.loc["net"] = total
step = blank.reset_index(drop=True).repeat(3).shift(-1)
step[1::3] = np.nan
blank.loc["net"] = 0
my_plot = trans.plot(kind='barh', stacked=True, bottom=blank,
                     legend=None, title="2014 Sales Waterfall")
my_plot.plot(step.index, step.values, 'k')
# my_plot.get_figure().savefig("waterfall.png", dpi=200, bbox_inches='tight')
plt.show()