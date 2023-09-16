import numpy as np
import matplotlib.pyplot as plt
import torch

def himmelblau(t):
    return (t[0] ** 2 + t[1] - 11) ** 2 + (t[0] + t[1] ** 2 - 7) ** 2+torch.sum(t*t)

def newfunc(t):
    return torch.sum(t*t)


def show_fig():
    x = np.arange(-6, 6, 0.1)
    y = np.arange(-6, 6, 0.1)
    X, Y = np.meshgrid(x, y)
    Z = himmelblau([X, Y])

    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    ax.plot_surface(X, Y, Z, cmap='coolwarm', linewidth=0, antialiased=False)
    # ax.view_init(60, -30)
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    plt.show()


def t_torch():
    import torch
    from tqdm import tqdm
    device='cuda'
    # x = torch.tensor([0., 0.,], requires_grad=True,device=device)
    x = torch.rand(100000,requires_grad=True,device=device)
    # x = torch.tensor([0., 0.], requires_grad=True)
    optimizer = torch.optim.Adam([x, ])
    for step in tqdm(range(30001)):
    # for step in range(100001):
        if step:
            optimizer.zero_grad()
            f.backward(retain_graph=True)
            optimizer.step()
        # f = himmelblau(x)
        f = newfunc(x)
        # if step % 10000 == 0:
        #     print('step:{} , x = {} , value = {}'.format(step, x.tolist(), f))
    print('step:{} , x = {} , value = {}'.format(step, x.tolist(), f))


if __name__ == "__main__":
    # show_fig()
    t_torch()
